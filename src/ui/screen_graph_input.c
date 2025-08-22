#include <lvgl.h>
#include <ui.h>
#include <text.h>
#include <screen_graph_input.h>

extern lv_obj_t *status_bar;

lv_obj_t *screen_graph_input;

lv_obj_t *input_area_y_1;
lv_obj_t *input_area_y_2;
lv_obj_t *input_area_y_3;
lv_obj_t *input_area_y_4;
lv_obj_t *input_area_y_5;

lv_obj_t *input_area_y_1_label;
lv_obj_t *input_area_y_2_label;
lv_obj_t *input_area_y_3_label;
lv_obj_t *input_area_y_4_label;
lv_obj_t *input_area_y_5_label;

char *input_buffer_y_1[MAXLEN_INPUT + 1], *output_buffer_y_1[MAXLEN_INPUT + 1];
char *input_buffer_y_2[MAXLEN_INPUT + 1], *output_buffer_y_2[MAXLEN_INPUT + 1];
char *input_buffer_y_3[MAXLEN_INPUT + 1], *output_buffer_y_3[MAXLEN_INPUT + 1];
char *input_buffer_y_4[MAXLEN_INPUT + 1], *output_buffer_y_4[MAXLEN_INPUT + 1];
char *input_buffer_y_5[MAXLEN_INPUT + 1], *output_buffer_y_5[MAXLEN_INPUT + 1];

int input_buffer_y_1_length, output_buffer_y_1_length = 0;
int input_buffer_y_2_length, output_buffer_y_2_length = 0;
int input_buffer_y_3_length, output_buffer_y_3_length = 0;
int input_buffer_y_4_length, output_buffer_y_4_length = 0;
int input_buffer_y_5_length, output_buffer_y_5_length = 0;

uint32_t input_buffer_y_1_current_pos = 0;
uint32_t input_buffer_y_2_current_pos = 0;
uint32_t input_buffer_y_3_current_pos = 0;
uint32_t input_buffer_y_4_current_pos = 0;
uint32_t input_buffer_y_5_current_pos = 0;

lv_obj_t *array_graph_input_screen[5];

int array_graph_input_screen_index = 0;

extern char current_screen;

void create_input_area_y_labels(void)
{
    input_area_y_1_label = lv_label_create(screen_graph_input);
    lv_obj_set_size(input_area_y_1_label, 50, 42);
    lv_obj_align_to(input_area_y_1_label, input_area_y_1, LV_ALIGN_LEFT_MID, -35, 9);
    lv_label_set_text(input_area_y_1_label, "Y\u2081 =");
    lv_obj_set_style_text_color(input_area_y_1_label, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_set_style_text_font(input_area_y_1_label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_label_set_recolor(input_area_y_1_label, true);

    input_area_y_2_label = lv_label_create(screen_graph_input);
    lv_obj_set_size(input_area_y_2_label, 50, 42);
    lv_obj_align_to(input_area_y_2_label, input_area_y_2, LV_ALIGN_LEFT_MID, -35, 9);
    lv_label_set_text(input_area_y_2_label, "Y\u2082 =");
    lv_obj_set_style_text_color(input_area_y_2_label, lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN);
    lv_obj_set_style_text_font(input_area_y_2_label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_label_set_recolor(input_area_y_2_label, true);

    input_area_y_3_label = lv_label_create(screen_graph_input);
    lv_obj_set_size(input_area_y_3_label, 50, 42);
    lv_obj_align_to(input_area_y_3_label, input_area_y_3, LV_ALIGN_LEFT_MID, -35, 9);
    lv_label_set_text(input_area_y_3_label, "Y\u2083 =");
    lv_obj_set_style_text_color(input_area_y_3_label, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
    lv_obj_set_style_text_font(input_area_y_3_label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_label_set_recolor(input_area_y_3_label, true);

    input_area_y_4_label = lv_label_create(screen_graph_input);
    lv_obj_set_size(input_area_y_4_label, 50, 42);
    lv_obj_align_to(input_area_y_4_label, input_area_y_4, LV_ALIGN_LEFT_MID, -35, 9);
    lv_label_set_text(input_area_y_4_label, "Y\u2084 =");
    lv_obj_set_style_text_color(input_area_y_4_label, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN);
    lv_obj_set_style_text_font(input_area_y_4_label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_label_set_recolor(input_area_y_4_label, true);

    input_area_y_5_label = lv_label_create(screen_graph_input);
    lv_obj_set_size(input_area_y_5_label, 50, 42);
    lv_obj_align_to(input_area_y_5_label, input_area_y_5, LV_ALIGN_LEFT_MID, -35, 9);
    lv_label_set_text(input_area_y_5_label, "Y\u2085 =");
    lv_obj_set_style_text_color(input_area_y_5_label, lv_palette_main(LV_PALETTE_PURPLE), LV_PART_MAIN);
    lv_obj_set_style_text_font(input_area_y_5_label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_label_set_recolor(input_area_y_5_label, true);
}

void create_input_area_y(void)
{
    static lv_style_t input_area_y_style;
    lv_style_init(&input_area_y_style);
    lv_style_set_size(&input_area_y_style, 270, 42);
    lv_style_set_bg_color(&input_area_y_style, lv_color_hex(BG_COLOR_INPUT_AREA));
    lv_style_set_border_width(&input_area_y_style, 0);
    lv_style_set_text_font(&input_area_y_style, FONT_INPUT_AREA);
    lv_style_set_text_color(&input_area_y_style, lv_color_hex(TEXT_COLOR));
    lv_style_set_radius(&input_area_y_style, 0);

    input_area_y_1 = lv_textarea_create(screen_graph_input);
    lv_textarea_set_one_line(input_area_y_1, true);
    lv_obj_align(input_area_y_1, LV_ALIGN_TOP_RIGHT, 0, -11);
    lv_obj_set_scrollbar_mode(input_area_y_1, LV_SCROLLBAR_MODE_OFF);
    lv_textarea_set_max_length(input_area_y_1, MAXLEN_INPUT);
    lv_obj_add_state(input_area_y_1, LV_STATE_FOCUSED);
    lv_obj_add_style(input_area_y_1, &input_area_y_style, LV_PART_MAIN);
    lv_obj_set_style_border_color(input_area_y_1, lv_color_hex(TEXT_COLOR), LV_PART_CURSOR | LV_STATE_FOCUSED);

    input_area_y_2 = lv_textarea_create(screen_graph_input);
    lv_textarea_set_one_line(input_area_y_2, true);
    lv_obj_align_to(input_area_y_2, input_area_y_1, LV_ALIGN_BOTTOM_MID, -5, 50);
    lv_obj_set_scrollbar_mode(input_area_y_2, LV_SCROLLBAR_MODE_OFF);
    lv_textarea_set_max_length(input_area_y_2, MAXLEN_INPUT);
    lv_obj_add_style(input_area_y_2, &input_area_y_style, LV_PART_MAIN);
    lv_obj_set_style_border_color(input_area_y_2, lv_color_hex(TEXT_COLOR), LV_PART_CURSOR | LV_STATE_FOCUSED);

    input_area_y_3 = lv_textarea_create(screen_graph_input);
    lv_textarea_set_one_line(input_area_y_3, true);
    lv_obj_align_to(input_area_y_3, input_area_y_2, LV_ALIGN_BOTTOM_MID, -5, 50);
    lv_obj_set_scrollbar_mode(input_area_y_3, LV_SCROLLBAR_MODE_OFF);
    lv_textarea_set_max_length(input_area_y_3, MAXLEN_INPUT);
    lv_obj_add_style(input_area_y_3, &input_area_y_style, LV_PART_MAIN);
    lv_obj_set_style_border_color(input_area_y_3, lv_color_hex(TEXT_COLOR), LV_PART_CURSOR | LV_STATE_FOCUSED);

    input_area_y_4 = lv_textarea_create(screen_graph_input);
    lv_textarea_set_one_line(input_area_y_4, true);
    lv_obj_align_to(input_area_y_4, input_area_y_3, LV_ALIGN_BOTTOM_MID, -5, 50);
    lv_obj_set_scrollbar_mode(input_area_y_4, LV_SCROLLBAR_MODE_OFF);
    lv_textarea_set_max_length(input_area_y_4, MAXLEN_INPUT);
    lv_obj_add_style(input_area_y_4, &input_area_y_style, LV_PART_MAIN);
    lv_obj_set_style_border_color(input_area_y_4, lv_color_hex(TEXT_COLOR), LV_PART_CURSOR | LV_STATE_FOCUSED);

    input_area_y_5 = lv_textarea_create(screen_graph_input);
    lv_textarea_set_one_line(input_area_y_5, true);
    lv_obj_align_to(input_area_y_5, input_area_y_4, LV_ALIGN_BOTTOM_MID, -5, 50);
    lv_obj_set_scrollbar_mode(input_area_y_5, LV_SCROLLBAR_MODE_OFF);
    lv_textarea_set_max_length(input_area_y_5, MAXLEN_INPUT);
    lv_obj_add_style(input_area_y_5, &input_area_y_style, LV_PART_MAIN);
    lv_obj_set_style_border_color(input_area_y_5, lv_color_hex(TEXT_COLOR), LV_PART_CURSOR | LV_STATE_FOCUSED);

    create_input_area_y_labels();
}

void create_screen_graph_input(void)
{
    screen_graph_input = lv_obj_create(lv_screen_active());
    lv_obj_set_size(screen_graph_input, 320, 210);
    lv_obj_align(screen_graph_input, LV_ALIGN_TOP_MID, 0, 30);
    lv_obj_set_style_border_width(screen_graph_input, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(screen_graph_input, 0, LV_PART_MAIN);
    lv_obj_remove_flag(screen_graph_input, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_style_bg_color(screen_graph_input, lv_color_hex(BG_COLOR_INPUT_AREA), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(screen_graph_input, LV_SCROLLBAR_MODE_OFF);
    create_input_area_y();

    array_graph_input_screen[0] = input_area_y_1;
    array_graph_input_screen[1] = input_area_y_2;
    array_graph_input_screen[2] = input_area_y_3;
    array_graph_input_screen[3] = input_area_y_4;
    array_graph_input_screen[4] = input_area_y_5;
}

void display_screen_graph_input(void)
{
    lv_obj_move_foreground(screen_graph_input);
    lv_obj_move_foreground(status_bar);
    current_screen = SCREEN_GRAPH_INPUT;
}

lv_obj_t *get_focused_input_y(void)
{
    switch (array_graph_input_screen_index) {
        case 0: return input_area_y_1;
        case 1: return input_area_y_2;
        case 2: return input_area_y_3;
        case 3: return input_area_y_4;
        case 4: return input_area_y_5;
    }
}
