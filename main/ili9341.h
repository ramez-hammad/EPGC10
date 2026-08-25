#ifndef ILI9341_H
#define ILI9341_H

#include <lvgl.h>

/* SPI wiring of the ILI9341 panel, see hardware/schematic.pdf */
#define ILI9341_PIN_MOSI 23
#define ILI9341_PIN_MISO 19
#define ILI9341_PIN_SCLK 18
#define ILI9341_PIN_CS   5
#define ILI9341_PIN_DC   12
#define ILI9341_PIN_RST  4

#define ILI9341_HOR_RES 240
#define ILI9341_VER_RES 320

#define ILI9341_SPI_HOST     SPI2_HOST
#define ILI9341_PIXEL_CLK_HZ (40 * 1000 * 1000)

void ili9341_init(void);
void ili9341_flush(lv_display_t *display, const lv_area_t *area, uint8_t *px_map);

#endif
