#include <SDL_timer.h>
#include <string.h>
#include <lvgl.h>
#include <button_matrix.h>
#include <ui.h>
#include <text.h>

lv_obj_t *input_area;
lv_obj_t *input_area_container;
lv_obj_t *line;
lv_obj_t *input_base;
lv_obj_t *ans_label;
lv_obj_t *display_format_label;
lv_obj_t *deg_rad_label;
lv_obj_t *status_bar;
lv_obj_t *screen_menu;
lv_obj_t *screen_menu_container;

lv_obj_t *back_button_menu;
lv_obj_t *back_button_menu_label;

lv_obj_t *graph_button_menu;
lv_obj_t *graph_button_menu_label;

lv_obj_t *menu_button_3;
lv_obj_t *menu_button_4;
lv_obj_t *menu_button_5;
lv_obj_t *menu_button_6;
lv_obj_t *menu_button_7;
lv_obj_t *menu_button_8;
lv_obj_t *menu_button_9;

lv_obj_t *array_mode_screen[3][3];

char current_screen;
char *display_format;
char deg_rad = 1;
double prev_ans;

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

void create_deg_rad_label(void)
{
    deg_rad_label = lv_label_create(status_bar);
    lv_obj_align_to(deg_rad_label, display_format_label, LV_ALIGN_RIGHT_MID, 35, 0);
    if (deg_rad == 1) lv_label_set_text(deg_rad_label, "DEGREE");
    if (deg_rad == 0) lv_label_set_text(deg_rad_label, "RADIAN");
    lv_obj_set_style_radius(deg_rad_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(deg_rad_label, lv_color_hex(0xffffff), LV_PART_MAIN);
}

void create_display_format_label(void)
{
    display_format_label = lv_label_create(status_bar);
    lv_obj_align(display_format_label, LV_ALIGN_TOP_LEFT, -15, -15);
    lv_label_set_text(display_format_label, display_format);
    lv_obj_set_style_radius(display_format_label, 0, LV_PART_MAIN);
    lv_obj_set_style_text_color(display_format_label, lv_color_hex(0xffffff), LV_PART_MAIN);
}

void create_status_bar(void)
{
    status_bar = lv_obj_create(lv_screen_active());
    lv_obj_set_size(status_bar, 320, 35);
    lv_obj_align(status_bar, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_scrollbar_mode(status_bar, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(status_bar, lv_color_hex(0x525552), LV_ANIM_IMAGE_PART_MAIN);
    lv_obj_set_style_radius(status_bar, 0, LV_PART_MAIN);
    lv_obj_set_style_border_width(status_bar, 2, LV_PART_MAIN);
    lv_obj_set_style_border_side(status_bar, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
    lv_obj_set_style_border_color(status_bar, lv_color_hex(0xffffff), LV_PART_MAIN);
    create_display_format_label();
    create_deg_rad_label();
}

void create_input_base(void)
{
    input_base = lv_obj_create(lv_screen_active());
    lv_obj_align(input_base, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(input_base, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_size(input_base, 320, 240);
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

void create_screen_menu(void)
{
    screen_menu = lv_obj_create(lv_screen_active());
    lv_obj_set_size(screen_menu, 320, 240);
    lv_obj_align(screen_menu, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_width(screen_menu, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(screen_menu, 0, LV_PART_MAIN);
    lv_obj_remove_flag(screen_menu, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_style_bg_color(screen_menu, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(screen_menu, LV_SCROLLBAR_MODE_OFF);
}

void create_screen_menu_container(void)
{
    screen_menu_container = lv_obj_create(screen_menu);
    lv_obj_set_style_bg_color(screen_menu_container, lv_color_hex(0xffffff), LV_PART_MAIN);
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
    lv_style_set_bg_color(&menu_button_style_default, lv_color_hex(0xffffff));

    static lv_style_t menu_button_style_focused;
    lv_style_init(&menu_button_style_focused);
    lv_style_set_bg_opa(&menu_button_style_focused, LV_OPA_MAX);
    lv_style_set_bg_color(&menu_button_style_focused, lv_color_hex(0xff0000));


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
}

int main(void)
{
    // Initialize LVGL
    lv_init();

    // Connect the Tick Interface
    lv_tick_set_cb(SDL_GetTicks);

    // Create window
    lv_display_t *lvDisplay = lv_sdl_window_create(370, 640);

    // Create mouse
    lv_indev_t *lv_mouse = lv_sdl_mouse_create();

    // Change the background color of the active screen
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x000000), LV_PART_MAIN);

    display_format = "NORMAL";

    current_screen = 0;

    // Create UI
    create_screen_menu();
    create_screen_menu_container();
    create_screen_menu_widgets();

    array_mode_screen[0][0] = back_button_menu;
    array_mode_screen[0][1] = graph_button_menu;
    array_mode_screen[0][2] = menu_button_3;
    array_mode_screen[1][0] = menu_button_4;
    array_mode_screen[1][1] = menu_button_5;
    array_mode_screen[1][2] = menu_button_6;
    array_mode_screen[2][0] = menu_button_7;
    array_mode_screen[2][1] = menu_button_8;
    array_mode_screen[2][2] = menu_button_9;

    create_input_base();
    create_input_area_container();
    create_input_area();
    create_status_bar();
    create_button_matrix_base();
    create_button_matrix();

    while (true) {
        lv_timer_handler();
    }
}
