#include <lvgl.h>
#include <string.h>
#include <button_matrix_callbacks.h>

extern lv_obj_t *input_area;
extern lv_obj_t *input_base;
extern lv_obj_t *line;

lv_obj_t *btn_matrix_base;
lv_obj_t *btn_matrix_part_down;
lv_obj_t *btn_matrix_part_mid_container;
lv_obj_t *btn_matrix_part_mid;
lv_obj_t *btn_matrix_part_mid_nav_container;
lv_obj_t *btn_matrix_part_mid_nav_1;
lv_obj_t *btn_matrix_part_mid_nav_2;
lv_obj_t *btn_matrix_part_mid_nav_3;
lv_obj_t *btn_matrix_part_mid_nav_4;
lv_obj_t *btn_matrix_part_mid_nav_5;
lv_obj_t *btn_matrix_part_up;

void create_button_matrix_base(void)
{
    btn_matrix_base = lv_obj_create(lv_screen_active());
    lv_obj_set_size(btn_matrix_base, 370, 400);
    lv_obj_align(btn_matrix_base, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_border_width(btn_matrix_base, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_base, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(btn_matrix_base, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flag(btn_matrix_base, LV_OBJ_FLAG_SCROLLABLE, false);
    lv_obj_set_style_radius(btn_matrix_base, 0, LV_PART_MAIN);
}

void create_button_matrix_part_down(void)
{
    static const char *btn_matrix_part_down_map[] = {
        " ", "log", "ln", "sin", "cos", "tan", "\n",
        " ", " ", "(", ")", ",", " ", "\n",
        "7", "8", "9", "DEL", "AC", "\n",
        "4", "5", "6", "X", "/", "\n",
        "1", "2", "3", "+", "-", "\n",
        "0", ".", "Pi", "Ans", "=", NULL
    };
    btn_matrix_part_down = lv_buttonmatrix_create(btn_matrix_base);
    lv_obj_set_size(btn_matrix_part_down, 370, 235);
    lv_obj_align(btn_matrix_part_down, LV_ALIGN_BOTTOM_MID, 0, 16);
    lv_obj_set_style_radius(btn_matrix_part_down, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_down, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn_matrix_part_down, 0, LV_PART_MAIN);
    lv_buttonmatrix_set_map(btn_matrix_part_down, btn_matrix_part_down_map);
    uint32_t index = lv_buttonmatrix_get_selected_button(btn_matrix_part_down);
    lv_obj_add_event_cb(btn_matrix_part_down, btn_matrix_down_cb, LV_EVENT_VALUE_CHANGED, &index);
}

void create_nav_sector(lv_obj_t **nav_sector, int ang_start, int ang_end, int x_offset, int y_offset, int width, int height)
{
    *nav_sector = lv_arc_create(btn_matrix_part_mid_nav_container);
    lv_obj_center(*nav_sector);
    lv_obj_align(*nav_sector, LV_ALIGN_CENTER, x_offset, y_offset);
    lv_obj_set_size(*nav_sector, width, height);
    lv_obj_remove_style(*nav_sector, NULL, LV_PART_KNOB);
    lv_arc_set_bg_angles(*nav_sector, ang_start, ang_end);
    lv_obj_set_style_arc_width(*nav_sector, 57, LV_PART_MAIN);
    lv_obj_set_style_arc_width(*nav_sector, 0, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(*nav_sector, false, LV_PART_MAIN);
}

void create_button_matrix_part_mid(void)
{
    btn_matrix_part_mid_container = lv_obj_create(btn_matrix_base);
    lv_obj_set_size(btn_matrix_part_mid_container, 370, 115);
    lv_obj_align_to(btn_matrix_part_mid_container, btn_matrix_part_down, LV_ALIGN_TOP_MID, 0, -130);
    lv_obj_set_style_radius(btn_matrix_part_mid_container, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_mid_container, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn_matrix_part_mid_container, 0, LV_PART_MAIN);

    static const char *btn_matrix_part_mid_map[] = {
        "SHIFT", "OPTN", "VARS", "MENU", "\n",
        "ALPHA", "x^2", "^", "EXIT", NULL,
    };


    btn_matrix_part_mid = lv_buttonmatrix_create(btn_matrix_part_mid_container);
    lv_obj_set_size(btn_matrix_part_mid, 230, 115);
    lv_obj_set_style_radius(btn_matrix_part_mid, 0, LV_PART_MAIN);
    lv_obj_align(btn_matrix_part_mid, LV_ALIGN_LEFT_MID, -15, 0);
    lv_obj_set_flag(btn_matrix_part_mid_container, LV_OBJ_FLAG_SCROLLABLE, false);
    lv_buttonmatrix_set_map(btn_matrix_part_mid, btn_matrix_part_mid_map);
    lv_obj_set_style_border_width(btn_matrix_part_mid, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_mid, lv_color_hex(0x000000), LV_PART_MAIN);
    uint32_t index = lv_buttonmatrix_get_selected_button(btn_matrix_part_mid);
    lv_obj_add_event_cb(btn_matrix_part_mid, btn_matrix_mid_cb, LV_EVENT_VALUE_CHANGED, &index);

    btn_matrix_part_mid_nav_container = lv_obj_create(btn_matrix_part_mid_container);
    lv_obj_set_size(btn_matrix_part_mid_nav_container, 140, 115);
    lv_obj_align(btn_matrix_part_mid_nav_container, LV_ALIGN_RIGHT_MID, 17, 0);
    lv_obj_set_flag(btn_matrix_part_mid_nav_container, LV_OBJ_FLAG_SCROLLABLE, false);
    lv_obj_set_style_bg_color(btn_matrix_part_mid_nav_container, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn_matrix_part_mid_nav_container, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(btn_matrix_part_mid_nav_container, 0, LV_PART_MAIN);

    // Left
    create_nav_sector(&btn_matrix_part_mid_nav_1, 135, 225, -1, 0, 110, 105);
    lv_obj_add_flag(btn_matrix_part_mid_nav_1, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(btn_matrix_part_mid_nav_1, nav_cb_left, LV_EVENT_CLICKED, NULL);

    // Right
    create_nav_sector(&btn_matrix_part_mid_nav_2, 315, 45, 1, 0, 110, 105);
    lv_obj_add_flag(btn_matrix_part_mid_nav_2, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(btn_matrix_part_mid_nav_2, nav_cb_right, LV_EVENT_CLICKED, NULL);

    // Up
    create_nav_sector(&btn_matrix_part_mid_nav_3, 225, 315, 0, -1, 110, 105);
    lv_obj_add_flag(btn_matrix_part_mid_nav_3, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(btn_matrix_part_mid_nav_3, nav_cb_up, LV_EVENT_CLICKED, NULL);

    // Down
    create_nav_sector(&btn_matrix_part_mid_nav_4, 45, 135, 0, 1, 110, 105);
    lv_obj_add_flag(btn_matrix_part_mid_nav_4, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_add_event_cb(btn_matrix_part_mid_nav_4, nav_cb_down, LV_EVENT_CLICKED, NULL);

    // Center
    create_nav_sector(&btn_matrix_part_mid_nav_5, 0, 360, -2, 0, 55, 50);
    lv_obj_set_style_arc_color(btn_matrix_part_mid_nav_5,  lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_flag(btn_matrix_part_mid_nav_5, LV_OBJ_FLAG_CLICKABLE, false);
}

void create_button_matrix_part_up(void)
{
    static const char *btn_matrix_part_up_map[] = {
        "F1", "F2", "F3", "F4", "F5", "F6", NULL
    };

    btn_matrix_part_up = lv_buttonmatrix_create(btn_matrix_base);
    lv_obj_set_size(btn_matrix_part_up, 370, 50);
    lv_obj_set_style_radius(btn_matrix_part_up, 0, LV_PART_MAIN);
    lv_obj_align(btn_matrix_part_up, LV_ALIGN_TOP_MID, 0, -17);
    lv_buttonmatrix_set_map(btn_matrix_part_up, btn_matrix_part_up_map);
    lv_obj_set_style_bg_color(btn_matrix_part_up, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn_matrix_part_up, 0, LV_PART_MAIN);
    uint32_t index = lv_buttonmatrix_get_selected_button(btn_matrix_part_up);
    lv_obj_add_event_cb(btn_matrix_part_up, btn_matrix_up_cb, LV_EVENT_VALUE_CHANGED, &index);
}

void create_button_matrix(void)
{
    create_button_matrix_part_down();
    create_button_matrix_part_mid();
    create_button_matrix_part_up();
}
