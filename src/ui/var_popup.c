#include <lvgl.h>
#include <math.h>

#include <ui.h>
#include <text.h>

lv_obj_t *var_popup_container;

bool var_popup_open = false;

lv_obj_t *input_area_var_1;
lv_obj_t *input_area_var_2;

char *input_buffer_var_1[2], *output_buffer_var_1[2];
char *input_buffer_var_2[MAXLEN_INPUT + 1], *output_buffer_var_2[MAXLEN_INPUT + 1];

int input_buffer_var_1_length, output_buffer_var_1_length = 0;
int input_buffer_var_2_length, output_buffer_var_2_length = 0;

uint32_t input_buffer_var_1_current_pos, output_buffer_var_1_current_pos = 0;
uint32_t input_buffer_var_2_current_pos, output_buffer_var_2_current_pos = 0;

char var_popup_index = 0;

lv_obj_t *array_var_popup[2];

void create_var_popup(void)
{
    lv_obj_t *label;

    // Create container
    var_popup_container = lv_obj_create(lv_screen_active());
    lv_obj_set_style_border_color(var_popup_container, lv_color_hex(BG_COLOR_MENU_SELECTED), LV_PART_MAIN);
    lv_obj_set_style_border_width(var_popup_container, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(var_popup_container, 0, LV_PART_MAIN);
    lv_obj_set_size(var_popup_container, ceil(0.85 * 320), ceil(0.60 * 240));
    lv_obj_align(var_popup_container, LV_ALIGN_TOP_MID, 0, 88);
    lv_obj_set_scrollbar_mode(var_popup_container, LV_SCROLLBAR_MODE_OFF);

    // Create title
    lv_obj_t *var_popup_title = lv_label_create(var_popup_container);
    lv_obj_remove_style_all(var_popup_title);
    lv_obj_add_flag(var_popup_title, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_set_size(var_popup_title, ceil(0.85 * 320) - 2, 20);
    lv_obj_align(var_popup_title, LV_ALIGN_TOP_MID, 0, -16);
    lv_obj_set_style_bg_color(var_popup_title, lv_color_hex(0x6a6573), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(var_popup_title, LV_OPA_MAX, LV_PART_MAIN);
    lv_obj_set_style_border_color(var_popup_title, lv_color_hex(0x343434), LV_PART_MAIN);
    lv_obj_set_style_border_width(var_popup_title, 1, LV_PART_MAIN);
    lv_obj_set_style_text_color(var_popup_title, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    lv_obj_set_style_text_font(var_popup_title, FONT, LV_PART_MAIN);
    lv_label_set_text(var_popup_title, "Define variable");
    lv_obj_set_style_text_align(var_popup_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    // Create input areas and labels
    static lv_style_t input_area_var_style;
    lv_style_init(&input_area_var_style);
    lv_style_set_size(&input_area_var_style, 43, 43);
    lv_style_set_bg_color(&input_area_var_style, lv_color_hex(BG_COLOR_INPUT_AREA));
    lv_style_set_border_width(&input_area_var_style, 1);
    lv_style_set_text_font(&input_area_var_style, FONT_INPUT_AREA);
    lv_style_set_text_color(&input_area_var_style, lv_color_hex(TEXT_COLOR));
    lv_style_set_radius(&input_area_var_style, 0);

    input_area_var_1 = lv_textarea_create(var_popup_container);
    lv_obj_set_state(input_area_var_1, LV_STATE_FOCUSED, true);
    lv_textarea_set_max_length(input_area_var_1, 1);
    lv_obj_add_style(input_area_var_1, &input_area_var_style, LV_PART_MAIN);
    lv_obj_set_style_border_color(input_area_var_1, lv_color_hex(TEXT_COLOR), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_set_style_translate_x(input_area_var_1, 50, LV_PART_MAIN);
    lv_obj_set_style_translate_y(input_area_var_1, 40, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(input_area_var_1, LV_SCROLLBAR_MODE_OFF);

    label = lv_label_create(var_popup_container);
    lv_obj_set_size(label, 42, 42);
    lv_obj_align_to(label, input_area_var_1, LV_ALIGN_LEFT_MID, -47, 9);
    lv_label_set_text(label, "VAR");
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);

    input_area_var_2 = lv_textarea_create(var_popup_container);
    lv_obj_add_style(input_area_var_2, &input_area_var_style, LV_PART_MAIN);
    lv_obj_set_style_border_color(input_area_var_2, lv_color_hex(TEXT_COLOR), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_set_style_translate_x(input_area_var_2, 175,LV_PART_MAIN);
    lv_obj_set_style_translate_y(input_area_var_2, 40, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(input_area_var_2, LV_SCROLLBAR_MODE_OFF);
    lv_textarea_set_one_line(input_area_var_2, true);

    label = lv_label_create(var_popup_container);
    lv_obj_set_size(label, 42, 42);
    lv_obj_align_to(label, input_area_var_2, LV_ALIGN_LEFT_MID, -47, 9);
    lv_label_set_text(label, "VAL");
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);

    // Create an array to store input areas
    array_var_popup[0] = input_area_var_1;
    array_var_popup[1] = input_area_var_2;

    // Create confirm label
    label = lv_label_create(var_popup_container);
    lv_obj_set_size(label, 102, 42);
    lv_label_set_text(label, "Confirm \U0001F852 =");
    lv_obj_set_style_translate_x(label, 13,LV_PART_MAIN);
    lv_obj_set_style_translate_y(label, 100, LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT, LV_PART_MAIN);
}

void display_var_popup(void)
{
    lv_obj_move_foreground(var_popup_container);
    lv_obj_remove_state(get_input_area(), LV_STATE_FOCUSED);
    var_popup_index = 0;
    lv_obj_set_state(array_var_popup[var_popup_index], LV_STATE_FOCUSED, true);
    var_popup_open = true;
}

lv_obj_t *get_focused_input_area_var(void)
{
    if (var_popup_index == 0) return input_area_var_1;
    if (var_popup_index == 1) return input_area_var_2;
}