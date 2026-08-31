#include <lvgl.h>
#include <ili9341.h>
#include <app.h>
#include <port.h>
#include <esp_timer.h>

static uint32_t tick_cb (void)
{
    return (uint32_t) (esp_timer_get_time() / 1000);
}

void port_create_input(void)
{
    /* The hardware has a physical 9x6 keypad, so there is no on-screen keypad.
       Scanning it is not implemented yet, so the keys reach nothing. */
}

lv_draw_buf_t *port_create_graph_draw_buf(void)
{
    /* Allocated from the heap: a static ARGB8888 buffer does not fit in ESP32 DRAM */
    static lv_draw_buf_t *draw_buf;
    if (draw_buf == NULL) draw_buf = lv_draw_buf_create(320, 210, LV_COLOR_FORMAT_RGB565, 0);

    return draw_buf;
}

void app_main(void)
{
    // Initialize LVGL
    lv_init();
    lv_tick_set_cb(tick_cb);

    ili9341_init();

    static lv_color_t buf1[240 * 40];
    lv_display_t *display = lv_display_create(240, 320);
    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, ili9341_flush);

    app_create_ui();
    app_run();
}
