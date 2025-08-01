#include <lvgl.h>
#include <screen_menu.h>
#include <ui.h>

extern lv_obj_t *screen_menu;
extern lv_obj_t *screen_menu_container;

extern lv_obj_t *back_button_menu;
extern lv_obj_t *back_button_menu_label;

extern lv_obj_t *graph_button_menu;
extern lv_obj_t *graph_button_menu_label;

extern lv_obj_t *menu_button_3;
extern lv_obj_t *menu_button_4;
extern lv_obj_t *menu_button_5;
extern lv_obj_t *menu_button_6;
extern lv_obj_t *menu_button_7;
extern lv_obj_t *menu_button_8;
extern lv_obj_t *menu_button_9;

extern lv_obj_t *array_menu_screen[3][3];

extern uint32_t col_index;
extern uint32_t row_index;

extern lv_obj_t *status_bar;

uint32_t num_menu_buttons;

void create_screen_menu_container(void)
{
    screen_menu_container = lv_obj_create(screen_menu);
    lv_obj_set_style_bg_color(screen_menu_container, lv_color_hex(BG_COLOR_INPUT_AREA), LV_PART_MAIN);
    lv_obj_set_size(screen_menu_container, 320, 210);
    lv_obj_set_style_radius(screen_menu_container, 0, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(screen_menu_container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(screen_menu_container, 0, LV_PART_MAIN);
    lv_obj_set_scroll_dir(screen_menu_container, LV_DIR_VER);
    lv_obj_set_layout(screen_menu_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(screen_menu_container, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(screen_menu_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_ALIGN_CENTER);
    lv_obj_align(screen_menu_container, LV_ALIGN_BOTTOM_MID, 0, lv_obj_get_style_pad_row(screen_menu_container, LV_PART_MAIN));
}

void create_screen_menu_widgets(void)
{
    // Create menu button styles

    static lv_style_t menu_button_style_default;
    lv_style_init(&menu_button_style_default);
    lv_style_set_bg_opa(&menu_button_style_default, LV_OPA_MAX);
    lv_style_set_bg_color(&menu_button_style_default, lv_color_hex(BG_COLOR_BUTTONS));
    //lv_style_set_border_width(&menu_button_style_default, 0);

    static lv_style_t menu_button_style_focused;
    lv_style_init(&menu_button_style_focused);
    lv_style_set_bg_opa(&menu_button_style_focused, LV_OPA_MAX);
    lv_style_set_bg_color(&menu_button_style_focused, lv_color_hex(BG_COLOR_MENU_SELECTED));
    lv_style_set_border_width(&menu_button_style_focused, 0);

    graph_button_menu = lv_obj_create(screen_menu_container);
    lv_obj_set_size(graph_button_menu, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(graph_button_menu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(graph_button_menu, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(graph_button_menu, &menu_button_style_focused, LV_STATE_FOCUSED);

    graph_button_menu_label = lv_label_create(graph_button_menu);
    lv_obj_align(graph_button_menu_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(graph_button_menu_label, "Graph");

    back_button_menu = lv_obj_create(screen_menu_container);
    lv_obj_set_size(back_button_menu, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(back_button_menu, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(back_button_menu, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(back_button_menu, &menu_button_style_focused, LV_STATE_FOCUSED);

    back_button_menu_label = lv_label_create(back_button_menu);
    lv_obj_align(back_button_menu_label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(back_button_menu_label, "Back");

    // Placeholder menu buttons

    menu_button_9 = lv_obj_create(screen_menu_container);
    lv_obj_set_size(menu_button_9, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(menu_button_9, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(menu_button_9, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(menu_button_9, &menu_button_style_focused, LV_STATE_FOCUSED);

    menu_button_8 = lv_obj_create(screen_menu_container);
    lv_obj_set_size(menu_button_8, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(menu_button_8, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(menu_button_8, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(menu_button_8, &menu_button_style_focused, LV_STATE_FOCUSED);

    menu_button_7 = lv_obj_create(screen_menu_container);
    lv_obj_set_size(menu_button_7, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(menu_button_7, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(menu_button_7, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(menu_button_7, &menu_button_style_focused, LV_STATE_FOCUSED);

    menu_button_6 = lv_obj_create(screen_menu_container);
    lv_obj_set_size(menu_button_6, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(menu_button_6, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(menu_button_6, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(menu_button_6, &menu_button_style_focused, LV_STATE_FOCUSED);

    menu_button_5 = lv_obj_create(screen_menu_container);
    lv_obj_set_size(menu_button_5, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(menu_button_5, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(menu_button_5, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(menu_button_5, &menu_button_style_focused, LV_STATE_FOCUSED);

    menu_button_4 = lv_obj_create(screen_menu_container);
    lv_obj_set_size(menu_button_4, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(menu_button_4, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(menu_button_4, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(menu_button_4, &menu_button_style_focused, LV_STATE_FOCUSED);

    menu_button_3 = lv_obj_create(screen_menu_container);
    lv_obj_set_size(menu_button_3, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
    lv_obj_set_scrollbar_mode(menu_button_3, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(menu_button_3, &menu_button_style_default, LV_STATE_DEFAULT);
    lv_obj_add_style(menu_button_3, &menu_button_style_focused, LV_STATE_FOCUSED);
}

void create_screen_menu(void)
{
    screen_menu = lv_obj_create(lv_screen_active());
    lv_obj_set_size(screen_menu, 320, 240);
    lv_obj_align(screen_menu, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(screen_menu, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(screen_menu, 0, LV_PART_MAIN);
    lv_obj_remove_flag(screen_menu, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_style_bg_color(screen_menu, lv_color_hex(BG_COLOR_INPUT_AREA), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(screen_menu, LV_SCROLLBAR_MODE_OFF);
    create_screen_menu_container();
    create_screen_menu_widgets();

    array_menu_screen[0][0] = back_button_menu;
    array_menu_screen[0][1] = graph_button_menu;
    array_menu_screen[0][2] = menu_button_3;
    array_menu_screen[1][0] = menu_button_4;
    array_menu_screen[1][1] = menu_button_5;
    array_menu_screen[1][2] = menu_button_6;
    array_menu_screen[2][0] = menu_button_7;
    array_menu_screen[2][1] = menu_button_8;
    array_menu_screen[2][2] = menu_button_9;
}

void display_screen_menu(void)
{
    for (uint32_t i = 0; i < 3; i++) {
        for (uint32_t j = 0; j < 3; j++) {
            lv_obj_set_state(array_menu_screen[i][j], LV_STATE_DEFAULT, true);
            lv_obj_remove_state(array_menu_screen[i][j], LV_STATE_FOCUSED);
        }
    }

    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);

    lv_obj_move_foreground(screen_menu);
    lv_obj_move_foreground(screen_menu_container);
    lv_obj_move_foreground(back_button_menu);
    lv_obj_move_foreground(graph_button_menu);
    lv_obj_move_foreground(status_bar);

    for (uint32_t i = 0; i < 3; i++) {
        for (uint32_t j = 0; j < 3; j++) {
            lv_obj_move_to_index(array_menu_screen[i][j], num_menu_buttons);
            num_menu_buttons++;
        }
    }
}
