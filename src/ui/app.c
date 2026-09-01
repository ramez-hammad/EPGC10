#include <lvgl.h>
#include <screen_menu.h>
#include <input_area.h>
#include <status_bar.h>
#include <app.h>
#include <port.h>
#include <screen_graph_input.h>
#include <screen_graph.h>
#include <screen_settings.h>
#include <unistd.h>
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

void app_create_ui(void)
{
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(BG_COLOR), LV_PART_MAIN);

    display_format = "NORMAL";

    current_screen = SCREEN_INPUT;

    create_error_popup();
    create_var_popup();
    create_toolbox_popup();
    create_screen_menu();
    create_screen_graph_input();
    create_screen_settings();
    create_screen_graph();
    port_create_input();
    create_status_bar();
    create_input_base();
    create_input_area();
    create_name_label();
}

void app_run(void)
{
    while (true) {
        lv_timer_handler();
        usleep(1000);
    }
}
