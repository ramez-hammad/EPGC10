#include <lvgl.h>
#include <string.h>
#include <button_matrix_down_callback.h>
#include <button_matrix_mid_callback.h>
#include <button_matrix_up_callback.h>
#include <button_matrix_nav_callback.h>
#include <ui.h>
#include <input_area.h>
#include <button_matrix_down_draw_callback.h>

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
lv_obj_t *btn_matrix_part_up;

void create_button_matrix_base(void)
{
    btn_matrix_base = lv_obj_create(lv_screen_active());
    lv_obj_set_size(btn_matrix_base, 370, WINDOW_HEIGHT - SCREEN_HEIGHT);
    lv_obj_align(btn_matrix_base, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_border_width(btn_matrix_base, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_base, lv_color_hex(BG_COLOR), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(btn_matrix_base, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_flag(btn_matrix_base, LV_OBJ_FLAG_SCROLLABLE, false);
    lv_obj_set_style_radius(btn_matrix_base, 0, LV_PART_MAIN);
}

void create_button_matrix_part_down(void)
{
    static const char *btn_matrix_part_down_map[] = {
        "#dc143c          A#\n   hyp", "#dc143c          B#\n   log", "#dc143c          C#\n    ln",
        "#c4a747 sin\u207B\u00B9##dc143c  D#\n   sin", "#c4a747 cos\u207B\u00B9##dc143c  E#\n   cos",
        "#c4a747 tan\u207B\u00B9##dc143c  F#\n   tan", "\n",
        "#dc143c         G#\n", "#dc143c         H#\n", "#dc143c          I#\n     (", "#dc143c          J#\n     )", "#dc143c          K#\n     ,", "#dc143c          L#\n", "\n",
        "#dc143c            M#\n      7", "#dc143c            N#\n      8", "#dc143c            O#\n      9", "#dc143c            P#\n    DEL", "#dc143c            Q#\n     AC", "\n",
        "#dc143c            R#\n      4", "#dc143c            S#\n      5", "#dc143c            T#\n      6", "#dc143c            U#\n      \u00D7", "#dc143c            V#\n      \u00F7", "\n",
        "#dc143c            W#\n      1", "#dc143c            X#\n      2", "#dc143c            Y#\n      3", "#dc143c            Z#\n      +", " -", "\n",
        "0", ".", "\u03C0", "Ans", "=", NULL
    };

    btn_matrix_part_down = lv_buttonmatrix_create(btn_matrix_base);
    lv_obj_set_size(btn_matrix_part_down, 370, 294);
    lv_obj_align(btn_matrix_part_down, LV_ALIGN_BOTTOM_MID, 0, 16);
    lv_obj_set_style_radius(btn_matrix_part_down, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_down, lv_color_hex(BG_COLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_down, lv_color_hex(BG_COLOR_BUTTONS), LV_PART_ITEMS);
    lv_obj_set_style_border_width(btn_matrix_part_down, 0, LV_PART_MAIN);
    lv_buttonmatrix_set_map(btn_matrix_part_down, btn_matrix_part_down_map);
    uint32_t index = lv_buttonmatrix_get_selected_button(btn_matrix_part_down);
    lv_obj_add_event_cb(btn_matrix_part_down, btn_matrix_down_draw_cb, LV_EVENT_DRAW_TASK_ADDED, NULL);
    lv_obj_add_flag(btn_matrix_part_down, LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS);
    lv_obj_add_event_cb(btn_matrix_part_down, btn_matrix_down_cb, LV_EVENT_VALUE_CHANGED, &index);
    lv_buttonmatrix_set_button_ctrl_all(btn_matrix_part_down, LV_BUTTONMATRIX_CTRL_RECOLOR);
    lv_obj_set_style_text_font(btn_matrix_part_down, FONT_MATH, LV_PART_ITEMS);
}

void create_nav_sector(lv_obj_t **nav_sector, int ang_start, int ang_end)
{
    *nav_sector = lv_arc_create(btn_matrix_part_mid_nav_container);
    lv_obj_center(*nav_sector);
    lv_obj_align(*nav_sector, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(*nav_sector, 115, 115);
    lv_obj_remove_style(*nav_sector, NULL, LV_PART_KNOB);
    lv_arc_set_bg_angles(*nav_sector, ang_start, ang_end);
    lv_obj_set_style_arc_width(*nav_sector, 35, LV_PART_MAIN);
    lv_obj_set_style_arc_width(*nav_sector, 0, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(*nav_sector, false, LV_PART_MAIN);
    lv_obj_set_style_border_width(*nav_sector, 0, LV_PART_MAIN);
    lv_obj_set_style_arc_color(*nav_sector, lv_color_hex(BG_COLOR_BUTTONS), LV_PART_MAIN);
    lv_obj_add_event_cb(*nav_sector, nav_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(*nav_sector, nav_cb, LV_EVENT_LONG_PRESSED, NULL);
    lv_obj_add_event_cb(*nav_sector, nav_cb, LV_EVENT_LONG_PRESSED_REPEAT, NULL);
    lv_obj_set_ext_click_area(*nav_sector, 300);
}

void create_button_matrix_part_mid(void)
{
    btn_matrix_part_mid_container = lv_obj_create(btn_matrix_base);
    lv_obj_set_size(btn_matrix_part_mid_container, 370, 144);
    lv_obj_align_to(btn_matrix_part_mid_container, btn_matrix_part_down, LV_ALIGN_TOP_MID, 0, -155);
    lv_obj_set_style_radius(btn_matrix_part_mid_container, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_mid_container, lv_color_hex(BG_COLOR), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn_matrix_part_mid_container, 0, LV_PART_MAIN);

    static const char *btn_matrix_part_mid_map[] = {
        "#c4a747 SHIFT#", "TLBX", "\U0001D465", "MENU", "\n",
        "#dc143c ALPHA#", "#c4a747 \u221A        #\n    \U0001D465\u00B2", "^", "EXIT", NULL,
    };


    btn_matrix_part_mid = lv_buttonmatrix_create(btn_matrix_part_mid_container);
    lv_obj_set_size(btn_matrix_part_mid, 255, 144);
    lv_obj_set_style_radius(btn_matrix_part_mid, 0, LV_PART_MAIN);
    lv_obj_align(btn_matrix_part_mid, LV_ALIGN_LEFT_MID, -16, 0);
    lv_obj_set_flag(btn_matrix_part_mid_container, LV_OBJ_FLAG_SCROLLABLE, false);
    lv_buttonmatrix_set_map(btn_matrix_part_mid, btn_matrix_part_mid_map);
    lv_obj_set_style_border_width(btn_matrix_part_mid, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_mid, lv_color_hex(BG_COLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_mid, lv_color_hex(BG_COLOR_BUTTONS), LV_PART_ITEMS);
    lv_obj_set_style_pad_right(btn_matrix_part_mid, 4, LV_PART_MAIN);
    lv_obj_set_style_text_font(btn_matrix_part_mid, FONT_MATH, LV_PART_ITEMS);

    uint32_t index = lv_buttonmatrix_get_selected_button(btn_matrix_part_mid);
    lv_obj_add_event_cb(btn_matrix_part_mid, btn_matrix_mid_cb, LV_EVENT_VALUE_CHANGED, &index);

    btn_matrix_part_mid_nav_container = lv_obj_create(btn_matrix_part_mid_container);
    lv_obj_set_size(btn_matrix_part_mid_nav_container, 115, 115);
    lv_obj_align(btn_matrix_part_mid_nav_container, LV_ALIGN_RIGHT_MID, 17, 0);
    lv_obj_remove_flag(btn_matrix_part_mid_nav_container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(btn_matrix_part_mid_nav_container, lv_color_hex(BG_COLOR), LV_PART_MAIN);
    lv_obj_set_style_border_width(btn_matrix_part_mid_nav_container, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(btn_matrix_part_mid_nav_container, 0, LV_PART_MAIN);
    lv_buttonmatrix_set_button_ctrl_all(btn_matrix_part_mid, LV_BUTTONMATRIX_CTRL_RECOLOR);

    // Left
    create_nav_sector(&btn_matrix_part_mid_nav_1, 135, 225);

    // Right
    create_nav_sector(&btn_matrix_part_mid_nav_2, 315, 45);

    // Up
    create_nav_sector(&btn_matrix_part_mid_nav_3, 225, 315);

    // Down
    create_nav_sector(&btn_matrix_part_mid_nav_4, 45, 135);
}

void create_button_matrix_part_up(void)
{
    static const char *btn_matrix_part_up_map[] = {
        "F1", "F2", "F3", "F4", "F5", "F6", NULL
    };

    btn_matrix_part_up = lv_buttonmatrix_create(btn_matrix_base);
    lv_obj_set_size(btn_matrix_part_up, 370, 62);
    lv_obj_set_style_radius(btn_matrix_part_up, 0, LV_PART_MAIN);
    lv_obj_align_to(btn_matrix_part_up, btn_matrix_part_mid,LV_ALIGN_TOP_MID, 52, -68);
    lv_buttonmatrix_set_map(btn_matrix_part_up, btn_matrix_part_up_map);
    lv_obj_set_style_bg_color(btn_matrix_part_up, lv_color_hex(BG_COLOR), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn_matrix_part_up, lv_color_hex(BG_COLOR_BUTTONS), LV_PART_ITEMS);
    lv_obj_set_style_border_width(btn_matrix_part_up, 0, LV_PART_MAIN);
    uint32_t index = lv_buttonmatrix_get_selected_button(btn_matrix_part_up);
    lv_obj_add_event_cb(btn_matrix_part_up, btn_matrix_up_cb, LV_EVENT_VALUE_CHANGED, &index);
}

void create_button_matrix(void)
{
    create_button_matrix_base();
    create_button_matrix_part_down();
    create_button_matrix_part_mid();
    create_button_matrix_part_up();
}
