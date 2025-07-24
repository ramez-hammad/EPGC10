#include <lvgl.h>
#include <SDL_timer.h>
#include <screen_menu.h>
#include <input_area.h>
#include <status_bar.h>
#include <button_matrix.h>
#include <ui.h>

lv_obj_t *input_area;
lv_obj_t *input_area_container;
lv_obj_t *line;
lv_obj_t *input_base;
lv_obj_t *ans_label;
lv_obj_t *display_format_label;
lv_obj_t *deg_rad_label;
lv_obj_t *status_bar;
lv_obj_t *screen_menu;
lv_obj_t *screen_menu_container;

lv_obj_t *back_button_menu;
lv_obj_t *back_button_menu_label;

lv_obj_t *graph_button_menu;
lv_obj_t *graph_button_menu_label;

lv_obj_t *menu_button_3;
lv_obj_t *menu_button_4;
lv_obj_t *menu_button_5;
lv_obj_t *menu_button_6;
lv_obj_t *menu_button_7;
lv_obj_t *menu_button_8;
lv_obj_t *menu_button_9;

lv_obj_t *array_mode_screen[3][3];

char current_screen;
char *display_format;
char deg_rad = 1;
double prev_ans;
char shift;

int main(void)
{
    // Initialize LVGL
    lv_init();

    // Connect the Tick Interface
    lv_tick_set_cb(SDL_GetTicks);

    // Create window
    lv_display_t *lvDisplay = lv_sdl_window_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    // Create mouse
    lv_indev_t *lv_mouse = lv_sdl_mouse_create();

    // Change the background color of the active screen
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);

    display_format = "NORMAL";

    current_screen = 0;

    // Create UI
    create_screen_menu();
    create_input_base();
    create_input_area_container();
    create_input_area();
    create_status_bar();
    create_button_matrix();

    while (true) {
        lv_timer_handler();
    }
}
