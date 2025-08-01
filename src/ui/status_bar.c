#include <lvgl.h>
#include <ui.h>

extern lv_obj_t* status_bar;
extern lv_obj_t* display_format_label;
extern lv_obj_t* deg_rad_label;

extern char deg_rad;
extern char *display_format;

void create_display_format_label(void)
{
    display_format_label = lv_label_create(status_bar);
    lv_obj_align(display_format_label, LV_ALIGN_TOP_LEFT, -15, -15);
    lv_label_set_text(display_format_label, display_format);
    lv_obj_set_style_radius(display_format_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(display_format_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
}

void create_deg_rad_label(void)
{
    deg_rad_label = lv_label_create(status_bar);
    lv_obj_align_to(deg_rad_label, display_format_label, LV_ALIGN_RIGHT_MID, 35, 0);
    if (deg_rad == 1) lv_label_set_text(deg_rad_label, "DEGREE");
    if (deg_rad == 0) lv_label_set_text(deg_rad_label, "RADIAN");
    lv_obj_set_style_radius(deg_rad_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(deg_rad_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
}

void create_status_bar(void)
{
    status_bar = lv_obj_create(lv_screen_active());
    lv_obj_set_size(status_bar, 320, 35);
    lv_obj_align(status_bar, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_scrollbar_mode(status_bar, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(status_bar, lv_color_hex(BG_COLOR_STATUS_BAR), LV_ANIM_IMAGE_PART_MAIN);
    lv_obj_set_style_radius(status_bar, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(status_bar, 2, LV_PART_MAIN);
    lv_obj_set_style_border_side(status_bar, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    lv_obj_set_style_border_color(status_bar, lv_color_hex(BG_COLOR_STATUS_BAR), LV_PART_MAIN);
    create_display_format_label();
    create_deg_rad_label();
}
