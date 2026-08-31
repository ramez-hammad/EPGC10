#include <ili9341.h>

#include <driver/spi_master.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_ili9341.h>

static esp_lcd_panel_handle_t panel_handle;
static lv_display_t *flushing_display;

static bool color_trans_done (esp_lcd_panel_io_handle_t io, esp_lcd_panel_io_event_data_t *event_data, void *user_ctx)
{
    if (flushing_display != NULL) lv_display_flush_ready(flushing_display);
    return false;
}

void ili9341_init (void)
{
    spi_bus_config_t bus_config = {
        .mosi_io_num = ILI9341_PIN_MOSI,
        .miso_io_num = ILI9341_PIN_MISO,
        .sclk_io_num = ILI9341_PIN_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = ILI9341_HOR_RES * 40 * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(ILI9341_SPI_HOST, &bus_config, SPI_DMA_CH_AUTO));

    esp_lcd_panel_io_handle_t io_handle;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = ILI9341_PIN_DC,
        .cs_gpio_num = ILI9341_PIN_CS,
        .pclk_hz = ILI9341_PIXEL_CLK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
        .on_color_trans_done = color_trans_done,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t) ILI9341_SPI_HOST, &io_config, &io_handle));

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = ILI9341_PIN_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel_handle));

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
}

void ili9341_flush (lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    flushing_display = display;

    uint32_t size = lv_area_get_width(area) * lv_area_get_height(area);
    lv_draw_sw_rgb565_swap(px_map, size);

    ESP_ERROR_CHECK(esp_lcd_panel_draw_bitmap(panel_handle, area->x1, area->y1, area->x2 + 1, area->y2 + 1, px_map));
}
