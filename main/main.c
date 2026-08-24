#include <lvgl.h>
#include <ili9341.h>
#include <screen_menu.h>
#include <input_area.h>
#include <status_bar.h>
#include <button_matrix.h>
#include <main.h>
#include <screen_graph_input.h>
#include <screen_graph.h>
#include <screen_settings.h>
#include <unistd.h>
#include <esp_timer.h>
#include <toolbox_popup.h>
#include <var_popup.h>
#include <error_popup.h>
#include <ui.h>

lv_obj_t *input_area;
lv_obj_t *input_area_container;
lv_obj_t *line;
lv_obj_t *input_base;
lv_obj_t *ans_label;

lv_obj_t *screen_menu;
lv_obj_t *screen_menu_container;

lv_obj_t *back_button_menu;
lv_obj_t *back_button_menu_label;

lv_obj_t *graph_button_menu;
lv_obj_t *graph_button_menu_label;

lv_obj_t *settings_button_menu;
lv_obj_t *settings_button_menu_label;

lv_obj_t *menu_button_4;
lv_obj_t *menu_button_5;
lv_obj_t *menu_button_6;
lv_obj_t *menu_button_7;
lv_obj_t *menu_button_8;
lv_obj_t *menu_button_9;

lv_obj_t *array_menu_screen[3][3];

char current_screen;

extern char *display_format;

double prev_ans;
char shift;
char alpha;

void create_name_label (void)
{
   lv_obj_t *name_label = lv_label_create(lv_screen_active());
    lv_label_set_text(name_label, "EPGCv1.0");
    lv_obj_set_style_text_font(name_label, &JuliaMono_Regular_20, LV_PART_MAIN);
    lv_obj_align(name_label, LV_ALIGN_TOP_LEFT, 24, 5);
    lv_obj_set_style_text_color(name_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
}

static uint32_t tick_cb (void)
{
    return (uint32_t) (esp_timer_get_time() / 1000);
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

    // Change the background color of the active screen
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(BG_COLOR), LV_PART_MAIN);

    display_format = "NORMAL";

    current_screen = SCREEN_INPUT;

    // Create UI
    create_error_popup();
    create_var_popup();
    create_toolbox_popup();
    create_screen_menu();
    create_screen_graph_input();
    create_screen_settings();
    create_screen_graph();
    create_status_bar();
    create_input_base();
    create_input_area();
    create_name_label();

    while (true) {
        lv_timer_handler();
        usleep(1000);
    }
}
