#include <lvgl.h>
#include <text.h>
#include <stdio.h>
#include <string.h>
#include <input_area.h>
#include <ui.h>

extern lv_obj_t *input_base;
extern lv_obj_t *input_area_container;
extern lv_obj_t *input_area;
extern lv_obj_t *line;
extern lv_obj_t *ans_label;
extern lv_obj_t *status_bar;

extern double prev_ans;

char *input_buffer_main[MAXLEN_INPUT + 1];
char *output_buffer_main[MAXLEN_INPUT + 1];

int input_buffer_main_length = 0;
int output_buffer_main_length = 0;

int current_input_length;
int current_output_length;

void create_input_base(void)
{
    input_base = lv_obj_create(lv_screen_active());
    lv_obj_align(input_base, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(input_base, lv_color_hex(BG_COLOR_INPUT_AREA), LV_PART_MAIN);
    lv_obj_set_style_border_width(input_base, 0, LV_PART_MAIN);
    lv_obj_set_size(input_base, SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_obj_set_style_radius(input_base, 0, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(input_base, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(input_base, LV_OBJ_FLAG_SCROLL_ELASTIC);
}

void create_input_area_container(void)
{
    input_area_container = lv_obj_create(input_base);
    lv_obj_align(input_area_container, LV_ALIGN_BOTTOM_MID, 0, 20);
    lv_obj_set_style_bg_color(input_area_container, lv_color_hex(BG_COLOR_INPUT_AREA), LV_PART_MAIN);
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
    lv_obj_set_style_text_font(input_area, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_style_text_color(input_area, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_color(input_area, lv_color_hex(BG_COLOR_INPUT_AREA), LV_PART_MAIN);
    lv_obj_set_style_border_color(input_area, lv_color_hex(TEXT_COLOR), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_textarea_set_max_length(input_area, MAXLEN_INPUT);
}

void create_line_ans(void)
{
    line = lv_line_create(input_area_container);
    static lv_point_precise_t line_points[] = {{10, 0}, {360, 0}};
    lv_line_set_points(line, line_points, 2);
    lv_obj_set_style_line_dash_width(line, 3, LV_PART_MAIN);
    lv_obj_set_style_line_dash_gap(line, 3, LV_PART_MAIN);
    lv_obj_align_to(line, input_area, LV_ALIGN_BOTTOM_MID, 0, 20);
    lv_obj_set_style_line_width(line, 2, LV_PART_MAIN);
    lv_obj_set_style_line_color(line, lv_color_hex(BG_COLOR_LINE), LV_PART_MAIN);
}

void create_ans_label(double ans)
{
    char text[500];
    sprintf(text, "%.2f", ans);
    if (strlen(text) >= 14) sprintf(text, "%e", ans);
    if (strcmp(text, "inf") == 0) strcpy(text, "Error");
    if (strcmp(text, "-inf") == 0) strcpy(text, "Error");
    if (strcmp(text, "nan") == 0) strcpy(text, "Error");
    ans_label = lv_label_create(input_area_container);
    lv_label_set_text(ans_label, text);
    lv_obj_set_style_bg_color(ans_label, lv_color_hex(BG_COLOR_INPUT_AREA), LV_PART_MAIN);
    lv_obj_align_to(ans_label, input_area, LV_ALIGN_BOTTOM_RIGHT, -25, 15);
    lv_obj_set_style_text_font(ans_label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_style_text_color(ans_label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    prev_ans = ans;
}

void display_screen_input(void)
{
    lv_obj_move_foreground(input_base);
    lv_obj_move_foreground(status_bar);
}

void add_to_input_area(char *text)
{
    if (strcmp(text, "p") == 0) {
        append_text(input_buffer_main, text, &input_buffer_main_length);
        append_text(output_buffer_main, "\u03c0\0", &output_buffer_main_length);
        lv_textarea_set_text(input_area, get_text(output_buffer_main, &output_buffer_main_length));
    } else if (strcmp(text, "*") == 0) {
        append_text(input_buffer_main, text, &input_buffer_main_length);
        append_text(output_buffer_main, "\u00D7\0", &output_buffer_main_length);
        lv_textarea_set_text(input_area, get_text(output_buffer_main, &output_buffer_main_length));
    } else if (strcmp(text, "/") == 0) {
        append_text(input_buffer_main, text, &input_buffer_main_length);
        append_text(output_buffer_main, "\u00F7\0", &output_buffer_main_length);
        lv_textarea_set_text(input_area, get_text(output_buffer_main, &output_buffer_main_length));
    } else if (strcmp(text, "arcsin(") == 0) {
        append_text(input_buffer_main, text, &input_buffer_main_length);
        append_text(output_buffer_main, "sin\u207B\u00B9(", &output_buffer_main_length);
        lv_textarea_set_text(input_area, get_text(output_buffer_main, &output_buffer_main_length));
    } else if (strcmp(text, "arccos(") == 0) {
        append_text(input_buffer_main, text, &input_buffer_main_length);
        append_text(output_buffer_main, "cos\u207B\u00B9(", &output_buffer_main_length);
        lv_textarea_set_text(input_area, get_text(output_buffer_main, &output_buffer_main_length));
    } else if (strcmp(text, "arctan(") == 0) {
        append_text(input_buffer_main, text, &input_buffer_main_length);
        append_text(output_buffer_main, "tan\u207B\u00B9(", &output_buffer_main_length);
        lv_textarea_set_text(input_area, get_text(output_buffer_main, &output_buffer_main_length));
    } else {
        append_text(get_buffer(0), text, get_length(0));
        append_text(get_buffer(1), text, get_length(1));
        lv_textarea_set_text(get_input_area(), get_text(get_buffer(1), get_length(1)));
    }
}

void delete_from_input_area(void)
{
    delete_text(input_buffer_main, &input_buffer_main_length);
    delete_text(output_buffer_main, &output_buffer_main_length);
    lv_textarea_set_text(input_area, get_text(output_buffer_main, &output_buffer_main_length));
}
