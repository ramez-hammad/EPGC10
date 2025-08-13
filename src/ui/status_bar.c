#include <lvgl.h>
#include <ui.h>

lv_obj_t *status_bar;

lv_obj_t *shift_label;
lv_obj_t *alpha_label;
lv_obj_t *hyp_label;
lv_obj_t *display_format_label;
lv_obj_t *deg_rad_label;

extern char shift;
extern char alpha;
extern char hyp;

char deg_rad = 0;
char *display_format;

void create_shift_label(void)
{
    shift_label = lv_label_create(status_bar);
    lv_obj_align(shift_label, LV_ALIGN_TOP_LEFT, -15, -15);
    lv_label_set_text(shift_label, "SHIFT");
    lv_obj_set_style_radius(shift_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_font(shift_label, FONT, LV_PART_MAIN);

    if (shift) {
        lv_obj_set_style_text_color(shift_label, lv_palette_main(LV_PALETTE_AMBER), LV_PART_MAIN);
    } else {
        lv_obj_set_style_text_color(shift_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    }
}

void create_alpha_label(void)
{
    alpha_label = lv_label_create(status_bar);
    lv_label_set_text(alpha_label, "ALPHA");
    lv_obj_align_to(alpha_label, shift_label, LV_ALIGN_RIGHT_MID, 53, 0);
    lv_obj_set_style_radius(alpha_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(alpha_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    lv_obj_set_style_text_font(alpha_label, FONT, LV_PART_MAIN);

    if (alpha) {
        lv_obj_set_style_text_color(alpha_label, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    } else {
        lv_obj_set_style_text_color(alpha_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    }
}

void create_hyp_label(void)
{
    hyp_label = lv_label_create(status_bar);
    lv_obj_align_to(hyp_label, alpha_label, LV_ALIGN_RIGHT_MID, 35, 0);
    lv_label_set_text(hyp_label, "HYP");
    lv_obj_set_style_radius(hyp_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_font(hyp_label, FONT, LV_PART_MAIN);

    if (hyp) {
        lv_obj_set_style_text_color(hyp_label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    } else {
        lv_obj_set_style_text_color(hyp_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    }
}

void create_display_format_label(void)
{
    display_format_label = lv_label_create(status_bar);
    lv_obj_align_to(display_format_label, hyp_label, LV_ALIGN_RIGHT_MID, 35, 0);
    lv_label_set_text(display_format_label, display_format);
    lv_obj_set_style_radius(display_format_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(display_format_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    lv_obj_set_style_text_font(display_format_label, FONT, LV_PART_MAIN);
}

void create_deg_rad_label(void)
{
    deg_rad_label = lv_label_create(status_bar);
    lv_obj_align_to(deg_rad_label, display_format_label, LV_ALIGN_RIGHT_MID, 35, 0);
    if (deg_rad == 0) lv_label_set_text(deg_rad_label, "DEGREE");
    if (deg_rad == 1) lv_label_set_text(deg_rad_label, "RADIAN");
    if (deg_rad == 2) lv_label_set_text(deg_rad_label, "GRADIAN");
    lv_obj_set_style_radius(deg_rad_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(deg_rad_label, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    lv_obj_set_style_text_font(deg_rad_label, FONT, LV_PART_MAIN);
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

    create_shift_label();
    create_alpha_label();
    create_hyp_label();

    create_display_format_label();
    create_deg_rad_label();
}

void refresh_status_bar(void)
{
    lv_obj_delete(deg_rad_label);
    lv_obj_delete(display_format_label);
    lv_obj_delete(hyp_label);
    lv_obj_delete(alpha_label);
    lv_obj_delete(shift_label);

    create_shift_label();
    create_alpha_label();
    create_hyp_label();
    create_display_format_label();
    create_deg_rad_label();
}
