#include <lvgl.h>
#include <SDL_timer.h>
#include <app.h>
#include <button_matrix.h>
#include <port.h>
#include <port_config.h>

void port_create_input(void)
{
    create_button_matrix();
}

lv_draw_buf_t *port_create_graph_draw_buf(void)
{
    LV_DRAW_BUF_DEFINE_STATIC(draw_buf, 320, 210, LV_COLOR_FORMAT_ARGB8888);
    LV_DRAW_BUF_INIT_STATIC(draw_buf);

    return &draw_buf;
}

int main(void)
{
    // Initialize LVGL
    lv_init();

    // Connect the Tick Interface
    lv_tick_set_cb(SDL_GetTicks);

    // Create window
    lv_display_t *lvDisplay = lv_sdl_window_create(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create mouse
    lv_indev_t *lv_mouse = lv_sdl_mouse_create();

    app_create_ui();
    app_run();
}
