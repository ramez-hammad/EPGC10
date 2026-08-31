#include <lvgl.h>
#include <math.h>

#include "text.h"
#include "ui.h"

lv_obj_t *error_popup_container;

lv_obj_t *error_label;

void create_error_popup(void)
{
    // Create container
    error_popup_container = lv_obj_create(lv_screen_active());
    lv_obj_set_style_bg_color(error_popup_container, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(error_popup_container, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(error_popup_container, 0, LV_PART_MAIN);
    lv_obj_set_size(error_popup_container, ceil(0.75 * 320), ceil(0.50 * 240));
    lv_obj_align(error_popup_container, LV_ALIGN_TOP_MID, 0, 101);
    lv_obj_set_scrollbar_mode(error_popup_container, LV_SCROLLBAR_MODE_OFF);

    // Create title
    lv_obj_t *error_popup_title = lv_label_create(error_popup_container);
    lv_obj_remove_style_all(error_popup_title);
    lv_obj_add_flag(error_popup_title, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_set_size(error_popup_title, ceil(0.55 * 320) - 2, 20);
    lv_obj_align(error_popup_title, LV_ALIGN_TOP_MID, 0, -16);
    lv_obj_set_style_bg_color(error_popup_title, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(error_popup_title, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(error_popup_title, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    lv_obj_set_style_text_font(error_popup_title, FONT, LV_PART_MAIN);
    lv_label_set_text(error_popup_title, "Warning");
    lv_obj_set_style_text_align(error_popup_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    // Create label
    error_label = lv_label_create(error_popup_container);
    lv_obj_set_style_text_font(error_label, FONT, LV_PART_MAIN);
    lv_obj_set_style_text_color(error_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    lv_obj_center(error_label);
}

void error_popup_timer(lv_timer_t * timer)
{
    lv_obj_move_background(error_popup_container);
    lv_obj_add_state(get_input_area(), LV_STATE_FOCUSED);
    lv_timer_delete(timer);
}

void display_error_popup(void)
{
    lv_obj_move_foreground(error_popup_container);
    lv_obj_remove_state(get_input_area(), LV_STATE_FOCUSED);
    lv_timer_t * timer = lv_timer_create(error_popup_timer, 1000, NULL);
}