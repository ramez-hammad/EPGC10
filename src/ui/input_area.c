#include <lvgl.h>
#include <text.h>
#include <stdio.h>
#include <string.h>
#include <input_area.h>

extern lv_obj_t *input_base;
extern lv_obj_t *input_area_container;
extern lv_obj_t *input_area;
extern lv_obj_t *line;
extern lv_obj_t *ans_label;

extern double prev_ans;

void create_input_base(void)
{
    input_base = lv_obj_create(lv_screen_active());
    lv_obj_align(input_base, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(input_base, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_size(input_base, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_set_style_radius(input_base, 0, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(input_base, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(input_base, LV_OBJ_FLAG_SCROLL_ELASTIC);
}

void create_input_area_container(void)
{
    input_area_container = lv_obj_create(input_base);
    lv_obj_align(input_area_container, LV_ALIGN_BOTTOM_MID, 0, 20);
    lv_obj_set_style_bg_color(input_area_container, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_size(input_area_container, 320, 210);
    lv_obj_set_style_radius(input_area_container, 0, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(input_area_container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(input_area_container, 0, LV_PART_MAIN);
    lv_obj_set_scroll_dir(input_area_container, LV_DIR_VER);
}

void create_input_area(void)
{
    input_area = lv_textarea_create(input_area_container);
    lv_textarea_set_one_line(input_area, true);
    lv_obj_add_state(input_area, LV_STATE_FOCUSED);
    lv_obj_align(input_area, LV_ALIGN_TOP_LEFT, -18, -18);
    lv_obj_set_size(input_area, 320, 42);
    lv_obj_set_style_border_width(input_area, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(input_area, 0, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(input_area, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_font(input_area, &lv_font_montserrat_16, LV_PART_MAIN);
    lv_textarea_set_max_length(input_area, MAXLEN_INPUT);
}

void create_line_ans(void)
{
    line = lv_line_create(input_area_container);
    static lv_point_precise_t line_points[] = {{10, 0}, {360, 0}};
    lv_line_set_points(line, line_points, 2);
    lv_obj_set_style_line_dash_width(line, 3, LV_PART_MAIN);
    lv_obj_set_style_line_dash_gap(line, 3, LV_PART_MAIN);
    lv_obj_set_style_bg_color(line, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_align_to(line, input_area, LV_ALIGN_BOTTOM_MID, 0, 20);
    lv_obj_set_style_line_width(line, 2, LV_PART_MAIN);
}

void create_ans_label(double ans)
{
    char text[500];
    sprintf(text, "%.2f", ans);
    if (strlen(text) >= 14) sprintf(text, "%e", ans);
    if (strcmp(text, "inf") == 0) strcpy(text, "Error");
    ans_label = lv_label_create(input_area_container);
    lv_label_set_text(ans_label, text);
    lv_obj_set_style_bg_color(ans_label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align_to(ans_label, input_area, LV_ALIGN_BOTTOM_RIGHT, -25, 15);
    lv_obj_set_style_text_font(ans_label, &lv_font_montserrat_16, LV_PART_MAIN);
    prev_ans = ans;
}
