#include <lvgl.h>
#include <tgmath.h>

#include <ui.h>
#include <toolbox_popup.h>
#include <text.h>

lv_obj_t *toolbox_popup_container;

lv_obj_t *toolbox_popup_title;

lv_obj_t *toolbox_popup_buttons_container;

lv_obj_t *toolbox_popup_abs_button;
lv_obj_t *toolbox_popup_root_button;
lv_obj_t *toolbox_popup_log_button;
lv_obj_t *toolbox_popup_calculus_button;
lv_obj_t *toolbox_popup_derivative_button;
lv_obj_t *toolbox_popup_integral_button;
lv_obj_t *toolbox_popup_trigonometry_button;
lv_obj_t *toolbox_popup_constants_button;
lv_obj_t *toolbox_popup_round_button;
lv_obj_t *toolbox_popup_ceil_button;
lv_obj_t *toolbox_popup_floor_button;
lv_obj_t *toolbox_popup_factor_button;

lv_obj_t *toolbox_popup_sum_button;

lv_obj_t *label;

bool toolbox_open = false;

lv_obj_t *array_toolbox_1[7];

char toolbox_1_index = 0;

void create_toolbox_popup(void)
{
    // Create container
    toolbox_popup_container = lv_obj_create(lv_screen_active());
    lv_obj_set_style_border_color(toolbox_popup_container, lv_color_hex(BG_COLOR_MENU_SELECTED), LV_PART_MAIN);
    lv_obj_set_style_border_width(toolbox_popup_container, 1, LV_PART_MAIN);
    lv_obj_set_style_radius(toolbox_popup_container, 0, LV_PART_MAIN);
    lv_obj_set_size(toolbox_popup_container, ceil(0.85 * 320), ceil(0.80 * 240));
    lv_obj_align(toolbox_popup_container, LV_ALIGN_TOP_MID, 0, 88);
    lv_obj_set_scrollbar_mode(toolbox_popup_container, LV_SCROLLBAR_MODE_OFF);

    // Create buttons container
    toolbox_popup_buttons_container = lv_obj_create(toolbox_popup_container);
    lv_obj_set_style_border_width(toolbox_popup_buttons_container, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(toolbox_popup_buttons_container, 0, LV_PART_MAIN);
    lv_obj_set_size(toolbox_popup_buttons_container, ceil(0.85 * 320), 220);
    lv_obj_align(toolbox_popup_buttons_container, LV_ALIGN_BOTTOM_MID, 0, 20);
    lv_obj_set_scrollbar_mode(toolbox_popup_buttons_container, LV_SCROLLBAR_MODE_OFF);

    // Create title
    toolbox_popup_title = lv_label_create(toolbox_popup_container);
    lv_obj_remove_style_all(toolbox_popup_title);
    lv_obj_add_flag(toolbox_popup_title, LV_OBJ_FLAG_IGNORE_LAYOUT);
    lv_obj_set_size(toolbox_popup_title, ceil(0.85 * 320) - 2, 20);
    lv_obj_align(toolbox_popup_title, LV_ALIGN_TOP_MID, 0, -16);
    lv_obj_set_style_bg_color(toolbox_popup_title, lv_color_hex(0x6a6573), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(toolbox_popup_title, LV_OPA_MAX, LV_PART_MAIN);
    lv_obj_set_style_border_color(toolbox_popup_title, lv_color_hex(0x343434), LV_PART_MAIN);
    lv_obj_set_style_border_width(toolbox_popup_title, 1, LV_PART_MAIN);
    lv_obj_set_style_text_color(toolbox_popup_title, lv_color_hex(TEXT_COLOR_STATUS_BAR), LV_PART_MAIN);
    lv_obj_set_style_text_font(toolbox_popup_title, FONT, LV_PART_MAIN);
    lv_label_set_text(toolbox_popup_title, "Toolbox");
    lv_obj_set_style_text_align(toolbox_popup_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);

    // Create button styles
    static lv_style_t toolbox_button_style_default;
    lv_style_init(&toolbox_button_style_default);
    lv_style_set_bg_opa(&toolbox_button_style_default, LV_OPA_MAX);
    lv_style_set_bg_color(&toolbox_button_style_default, lv_color_hex(BG_COLOR_BUTTONS));
    lv_style_set_border_color(&toolbox_button_style_default, lv_color_hex(0xd3d3d3));
    lv_style_set_text_color(&toolbox_button_style_default, lv_color_hex(TEXT_COLOR));
    lv_style_set_text_font(&toolbox_button_style_default, FONT);
    lv_style_set_size(&toolbox_button_style_default, ceil(0.85 * 320), 30);
    lv_style_set_radius(&toolbox_button_style_default, 0);
    lv_style_set_border_width(&toolbox_button_style_default, 1);

    static lv_style_t toolbox_button_style_focused;
    lv_style_init(&toolbox_button_style_focused);
    lv_style_set_bg_opa(&toolbox_button_style_focused, LV_OPA_MAX);
    lv_style_set_bg_color(&toolbox_button_style_focused, lv_color_hex(BG_COLOR_MENU_SELECTED));
    lv_style_set_border_color(&toolbox_button_style_focused, lv_color_hex(0xd3d3d3));
    lv_style_set_text_color(&toolbox_button_style_focused, lv_color_hex(TEXT_COLOR));
    lv_style_set_text_font(&toolbox_button_style_focused, FONT);
    lv_style_set_size(&toolbox_button_style_focused, ceil(0.85 * 320), 30);
    lv_style_set_radius(&toolbox_button_style_focused, 0);
    lv_style_set_border_width(&toolbox_button_style_focused, 1);

    // Create buttons

    // Absolute value button
    toolbox_popup_abs_button = lv_obj_create(toolbox_popup_buttons_container);
    lv_obj_align(toolbox_popup_abs_button, LV_ALIGN_TOP_MID, 0, 30);
    lv_obj_set_scrollbar_mode(toolbox_popup_abs_button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(toolbox_popup_abs_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(toolbox_popup_abs_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(toolbox_popup_abs_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    // Create name and description labels
    label = lv_label_create(toolbox_popup_abs_button);
    lv_label_set_text(label, " abs(x)");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    label = lv_label_create(toolbox_popup_abs_button);
    lv_label_set_text(label, "Absolute value ");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    // Root button
    toolbox_popup_root_button = lv_obj_create(toolbox_popup_buttons_container);
    lv_obj_align_to(toolbox_popup_root_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 10);
    lv_obj_set_scrollbar_mode(toolbox_popup_root_button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(toolbox_popup_root_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(toolbox_popup_root_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(toolbox_popup_root_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    // Create name and description labels
    label = lv_label_create(toolbox_popup_root_button);
    lv_label_set_text(label, " root(x,n)");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    label = lv_label_create(toolbox_popup_root_button);
    lv_label_set_text(label, "nth root ");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    // Log button
    toolbox_popup_log_button = lv_obj_create(toolbox_popup_buttons_container);
    lv_obj_align_to(toolbox_popup_log_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 39);
    lv_obj_set_scrollbar_mode(toolbox_popup_log_button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(toolbox_popup_log_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(toolbox_popup_log_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(toolbox_popup_log_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    // Create name and description labels
    label = lv_label_create(toolbox_popup_log_button);
    lv_label_set_text(label, " log(x,a)");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    label = lv_label_create(toolbox_popup_log_button);
    lv_label_set_text(label, "Logarithm base a ");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    // Round button
    toolbox_popup_round_button = lv_obj_create(toolbox_popup_buttons_container);
    lv_obj_align_to(toolbox_popup_round_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 68);
    lv_obj_set_scrollbar_mode(toolbox_popup_round_button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(toolbox_popup_round_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(toolbox_popup_round_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(toolbox_popup_round_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    // Create name and description labels
    label = lv_label_create(toolbox_popup_round_button);
    lv_label_set_text(label, " round(x,n)");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    label = lv_label_create(toolbox_popup_round_button);
    lv_label_set_text(label, "Round to n digits ");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    // Calculus button
    toolbox_popup_calculus_button = lv_obj_create(toolbox_popup_buttons_container);
    lv_obj_align_to(toolbox_popup_calculus_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 97);
    lv_obj_set_scrollbar_mode(toolbox_popup_calculus_button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(toolbox_popup_calculus_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(toolbox_popup_calculus_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(toolbox_popup_calculus_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    // Create name and description labels
    label = lv_label_create(toolbox_popup_calculus_button);
    lv_label_set_text(label, " Calculus");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    label = lv_label_create(toolbox_popup_calculus_button);
    lv_label_set_text(label, "\U0001F852 ");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    // Trigonometry button
    toolbox_popup_trigonometry_button = lv_obj_create(toolbox_popup_buttons_container);
    lv_obj_align_to(toolbox_popup_trigonometry_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 126);
    lv_obj_set_scrollbar_mode(toolbox_popup_trigonometry_button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(toolbox_popup_trigonometry_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(toolbox_popup_trigonometry_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(toolbox_popup_trigonometry_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    // Create name and description labels
    label = lv_label_create(toolbox_popup_trigonometry_button);
    lv_label_set_text(label, " Trigonometry");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    label = lv_label_create(toolbox_popup_trigonometry_button);
    lv_label_set_text(label, "\U0001F852 ");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    // Constants button
    toolbox_popup_constants_button = lv_obj_create(toolbox_popup_buttons_container);
    lv_obj_align_to(toolbox_popup_constants_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 155);
    lv_obj_set_scrollbar_mode(toolbox_popup_constants_button, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(toolbox_popup_constants_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(toolbox_popup_constants_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(toolbox_popup_constants_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    // Create name and description labels
    label = lv_label_create(toolbox_popup_constants_button);
    lv_label_set_text(label, " Constants");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    label = lv_label_create(toolbox_popup_constants_button);
    lv_label_set_text(label, "\U0001F852 ");
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    lv_obj_set_size(label, ceil(0.85 * 320), 30);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    //// Log button (Placeholder)
    //toolbox_popup_log_button = lv_obj_create(toolbox_popup_buttons_container);
    //lv_obj_align_to(toolbox_popup_log_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 184);
    //lv_obj_set_scrollbar_mode(toolbox_popup_log_button, LV_SCROLLBAR_MODE_OFF);
    //lv_obj_remove_flag(toolbox_popup_log_button, LV_OBJ_FLAG_SCROLLABLE);
    //lv_obj_add_style(toolbox_popup_log_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    //lv_obj_add_style(toolbox_popup_log_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    //// Create name and description labels
    //label = lv_label_create(toolbox_popup_log_button);
    //lv_label_set_text(label, " log(x,a)");
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    //lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    //lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    //lv_obj_set_size(label, ceil(0.85 * 320), 30);
    //lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    //label = lv_label_create(toolbox_popup_log_button);
    //lv_label_set_text(label, "Logarithm base a ");
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    //lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    //lv_obj_set_style_text_font(label, FONT, LV_PART_MAIN);
    //lv_obj_set_size(label, ceil(0.85 * 320), 30);
    //lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    //// Log button (Placeholder)
    //toolbox_popup_log_button = lv_obj_create(toolbox_popup_buttons_container);
    //lv_obj_align_to(toolbox_popup_log_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 213);
    //lv_obj_set_scrollbar_mode(toolbox_popup_log_button, LV_SCROLLBAR_MODE_OFF);
    //lv_obj_remove_flag(toolbox_popup_log_button, LV_OBJ_FLAG_SCROLLABLE);
    //lv_obj_add_style(toolbox_popup_log_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    //lv_obj_add_style(toolbox_popup_log_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    //// Create name and description labels
    //label = lv_label_create(toolbox_popup_log_button);
    //lv_label_set_text(label, " log(x,a)");
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    //lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    //lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    //lv_obj_set_size(label, ceil(0.85 * 320), 30);
    //lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    //label = lv_label_create(toolbox_popup_log_button);
    //lv_label_set_text(label, "Logarithm base a ");
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    //lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    //lv_obj_set_style_text_font(label, FONT, LV_PART_MAIN);
    //lv_obj_set_size(label, ceil(0.85 * 320), 30);
    //lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    //// Log button (Placeholder)
    //toolbox_popup_log_button = lv_obj_create(toolbox_popup_buttons_container);
    //lv_obj_align_to(toolbox_popup_log_button, toolbox_popup_abs_button, LV_ALIGN_TOP_LEFT, -17, 242);
    //lv_obj_set_scrollbar_mode(toolbox_popup_log_button, LV_SCROLLBAR_MODE_OFF);
    //lv_obj_remove_flag(toolbox_popup_log_button, LV_OBJ_FLAG_SCROLLABLE);
    //lv_obj_add_style(toolbox_popup_log_button, &toolbox_button_style_default, LV_STATE_DEFAULT);
    //lv_obj_add_style(toolbox_popup_log_button, &toolbox_button_style_focused, LV_STATE_FOCUSED);

    //// Create name and description labels
    //label = lv_label_create(toolbox_popup_log_button);
    //lv_label_set_text(label, " log(x,a)");
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    //lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR), LV_PART_MAIN);
    //lv_obj_set_style_text_font(label, FONT_INPUT_AREA, LV_PART_MAIN);
    //lv_obj_set_size(label, ceil(0.85 * 320), 30);
    //lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -12);
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);

    //label = lv_label_create(toolbox_popup_log_button);
    //lv_label_set_text(label, "Logarithm base a ");
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN);
    //lv_obj_set_style_text_color(label, lv_color_hex(TEXT_COLOR_DESCRIPTION_LABEL), LV_PART_MAIN);
    //lv_obj_set_style_text_font(label, FONT, LV_PART_MAIN);
    //lv_obj_set_size(label, ceil(0.85 * 320), 30);
    //lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -10);
    //lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN);

    // Add buttons to array
    array_toolbox_1[0] = toolbox_popup_abs_button;
    array_toolbox_1[1] = toolbox_popup_root_button;
    array_toolbox_1[2] = toolbox_popup_log_button;
    array_toolbox_1[3] = toolbox_popup_round_button;
    array_toolbox_1[4] = toolbox_popup_calculus_button;
    array_toolbox_1[5] = toolbox_popup_trigonometry_button;
    array_toolbox_1[6] = toolbox_popup_constants_button;

    lv_obj_set_state(array_toolbox_1[toolbox_1_index], LV_STATE_FOCUSED, true);
}

void display_toolbox_popup(void)
{
    lv_obj_move_foreground(toolbox_popup_container);
    lv_obj_remove_state(get_input_area(), LV_STATE_FOCUSED);
    toolbox_open = true;
}
