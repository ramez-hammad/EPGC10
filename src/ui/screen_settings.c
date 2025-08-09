#include <lvgl.h>
#include <input_area.h>
#include <screen_settings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ui.h>

#include "src/widgets/menu/lv_menu_private.h"

lv_obj_t *screen_settings;

lv_obj_t *root_page;

lv_obj_t *angle_section;
lv_obj_t *result_format_section;

lv_obj_t *angle_page;
lv_obj_t *deg_section_angle_page;
lv_obj_t *rad_section_angle_page;
lv_obj_t *grad_section_angle_page;

lv_obj_t *result_format_page;
lv_obj_t *normal_section_result_format_page;
lv_obj_t *sci_section_result_format_page;
lv_obj_t *eng_section_result_format_page;
lv_obj_t *dec_section_result_format_page;

lv_obj_t *array_settings_section[2];
lv_obj_t *array_settings_angle_section[3];
lv_obj_t *array_settings_result_format_section[3];

char screen_settings_index = 0;
char screen_settings_angle_index = 0;
char screen_settings_result_format_index = 0;

extern char current_screen;

void create_screen_settings(void)
{
    // Create menu button styles

    static lv_style_t menu_button_style_default;
    lv_style_init(&menu_button_style_default);
    lv_style_set_bg_opa(&menu_button_style_default, LV_OPA_MAX);
    lv_style_set_bg_color(&menu_button_style_default, lv_color_hex(BG_COLOR_BUTTONS));
    lv_style_set_border_color(&menu_button_style_default, lv_color_hex(0xd3d3d3));
    lv_style_set_text_color(&menu_button_style_default, lv_color_hex(TEXT_COLOR));
    lv_style_set_text_font(&menu_button_style_default, FONT);

    static lv_style_t menu_button_style_focused;
    lv_style_init(&menu_button_style_focused);
    lv_style_set_bg_opa(&menu_button_style_focused, LV_OPA_MAX);
    lv_style_set_bg_color(&menu_button_style_focused, lv_color_hex(0xd5d6e6));
    lv_style_set_border_width(&menu_button_style_focused, 0);
    lv_style_set_text_color(&menu_button_style_focused, lv_color_hex(TEXT_COLOR));
    lv_style_set_text_font(&menu_button_style_focused, FONT);

    screen_settings = lv_menu_create(lv_screen_active());
    lv_obj_set_size(screen_settings, SCREEN_WIDTH, SCREEN_HEIGHT - 30);
    lv_obj_align(screen_settings, LV_ALIGN_TOP_MID, 0, 30);

    lv_obj_t *label;

    // Create angle sub-page
    angle_page = lv_menu_page_create(screen_settings, NULL);

    deg_section_angle_page = lv_menu_cont_create(angle_page);
    label = lv_label_create(deg_section_angle_page);
    lv_obj_add_flag(deg_section_angle_page, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_remove_style_all(deg_section_angle_page);
    lv_obj_align(deg_section_angle_page, LV_ALIGN_TOP_MID, 0, 15);
    lv_obj_set_style_border_width(deg_section_angle_page, 1, LV_PART_MAIN);
    lv_obj_set_size(deg_section_angle_page, 280, 40);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_label_set_text(label, " Degrees                                                 90\u00B0");
    lv_obj_add_style(deg_section_angle_page, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(deg_section_angle_page, &menu_button_style_focused, LV_STATE_FOCUSED);

    rad_section_angle_page = lv_menu_cont_create(angle_page);
    label = lv_label_create(rad_section_angle_page);
    lv_obj_add_flag(rad_section_angle_page, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_remove_style_all(rad_section_angle_page);
    lv_obj_align_to(rad_section_angle_page, deg_section_angle_page, LV_ALIGN_TOP_MID, 20, 38);
    lv_obj_set_style_border_width(rad_section_angle_page, 1, LV_PART_MAIN);
    lv_obj_set_size(rad_section_angle_page, 280, 40);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_label_set_text(label, " Radians                                                    \u03c0");
    lv_obj_add_style(rad_section_angle_page, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(rad_section_angle_page, &menu_button_style_focused, LV_STATE_FOCUSED);

    grad_section_angle_page = lv_menu_cont_create(angle_page);
    label = lv_label_create(grad_section_angle_page);
    lv_obj_add_flag(grad_section_angle_page, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_remove_style_all(grad_section_angle_page);
    lv_obj_align_to(grad_section_angle_page, rad_section_angle_page, LV_ALIGN_TOP_MID, -93, 38);
    lv_obj_set_style_border_width(grad_section_angle_page, 1, LV_PART_MAIN);
    lv_obj_set_size(grad_section_angle_page, 280, 40);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_label_set_text(label, " Gradians                                       100 gon");
    lv_obj_add_style(grad_section_angle_page, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(grad_section_angle_page, &menu_button_style_focused, LV_STATE_FOCUSED);

    // Create result format sub-page
    result_format_page = lv_menu_page_create(screen_settings, NULL);

    normal_section_result_format_page = lv_menu_cont_create(result_format_page);
    label = lv_label_create(normal_section_result_format_page);
    lv_obj_add_flag(normal_section_result_format_page, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_remove_style_all(normal_section_result_format_page);
    lv_obj_align(normal_section_result_format_page, LV_ALIGN_TOP_MID, 0, 15);
    lv_obj_set_style_border_width(normal_section_result_format_page, 1, LV_PART_MAIN);
    lv_obj_set_size(normal_section_result_format_page, 280, 40);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_label_set_text(label, " Normal");
    lv_obj_add_style(normal_section_result_format_page, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(normal_section_result_format_page, &menu_button_style_focused, LV_STATE_FOCUSED);

    sci_section_result_format_page = lv_menu_cont_create(result_format_page);
    label = lv_label_create(sci_section_result_format_page);
    lv_obj_add_flag(sci_section_result_format_page, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_remove_style_all(sci_section_result_format_page);
    lv_obj_align_to(sci_section_result_format_page, normal_section_result_format_page, LV_ALIGN_TOP_MID, 20, 38);
    lv_obj_set_style_border_width(sci_section_result_format_page, 1, LV_PART_MAIN);
    lv_obj_set_size(sci_section_result_format_page, 280, 40);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_label_set_text(label, " Scientific");
    lv_obj_add_style(sci_section_result_format_page, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(sci_section_result_format_page, &menu_button_style_focused, LV_STATE_FOCUSED);

    eng_section_result_format_page = lv_menu_cont_create(result_format_page);
    label = lv_label_create(eng_section_result_format_page);
    lv_obj_add_flag(eng_section_result_format_page, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_remove_style_all(eng_section_result_format_page);
    lv_obj_align_to(eng_section_result_format_page, sci_section_result_format_page, LV_ALIGN_TOP_MID, -93, 38);
    lv_obj_set_style_border_width(eng_section_result_format_page, 1, LV_PART_MAIN);
    lv_obj_set_size(eng_section_result_format_page, 280, 40);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_label_set_text(label, " Engineering");
    lv_obj_add_style(eng_section_result_format_page, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(eng_section_result_format_page, &menu_button_style_focused, LV_STATE_FOCUSED);

    // Create root page
    root_page = lv_menu_page_create(screen_settings, NULL);

    angle_section = lv_menu_cont_create(root_page);
    label = lv_label_create(angle_section);
    lv_label_set_text(label, " Angle measure");
    lv_menu_set_load_page_event(screen_settings, angle_section, angle_page);
    lv_obj_add_flag(angle_section, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_remove_style_all(angle_section);
    lv_obj_align(angle_section, LV_ALIGN_TOP_MID, 0, 15);
    lv_obj_set_style_border_width(angle_section, 1, LV_PART_MAIN);
    lv_obj_set_size(angle_section, 280, 40);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_add_style(angle_section, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(angle_section, &menu_button_style_focused, LV_STATE_FOCUSED);

    result_format_section = lv_menu_cont_create(root_page);
    label = lv_label_create(result_format_section);
    lv_label_set_text(label, " Result format");
    lv_menu_set_load_page_event(screen_settings, result_format_section, result_format_page);
    lv_obj_add_flag(result_format_section, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_remove_style_all(result_format_section);
    lv_obj_align_to(result_format_section, angle_section, LV_ALIGN_BOTTOM_MID, 20, 17);
    lv_obj_set_style_border_width(result_format_section, 1, LV_PART_MAIN);
    lv_obj_set_size(result_format_section, 280, 40);
    lv_obj_add_flag(label, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_add_style(result_format_section, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(result_format_section, &menu_button_style_focused, LV_STATE_FOCUSED);

    lv_menu_set_page(screen_settings, root_page);

    array_settings_section[0] = angle_section;
    array_settings_section[1] = result_format_section;

    array_settings_angle_section[0] = deg_section_angle_page;
    array_settings_angle_section[1] = rad_section_angle_page;
    array_settings_angle_section[2] = grad_section_angle_page;

    array_settings_result_format_section[0] = normal_section_result_format_page;
    array_settings_result_format_section[1] = sci_section_result_format_page;
    array_settings_result_format_section[2] = eng_section_result_format_page;

    lv_obj_set_size(lv_menu_get_main_header_back_button(screen_settings), 0, 0);
}

void display_screen_settings(void)
{
    lv_obj_move_foreground(screen_settings);
    lv_obj_set_state(array_settings_section[screen_settings_index], LV_STATE_FOCUSED, true);
    lv_obj_set_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_FOCUSED, true);
    lv_obj_set_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_FOCUSED, true);
    lv_obj_send_event(lv_menu_get_main_header_back_button(screen_settings), LV_EVENT_CLICKED, NULL);
    current_screen = SCREEN_SETTINGS;
}
