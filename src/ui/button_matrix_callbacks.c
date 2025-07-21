#include <lvgl.h>
#include <string.h>
#include <ui.h>
#include <interpreter.h>
#include <math.h>

extern lv_obj_t *input_base;
extern lv_obj_t *screen_menu;
extern lv_obj_t *screen_menu_container;
extern lv_obj_t *line;
extern lv_obj_t *input_area;
extern lv_obj_t *input_area_container;
extern lv_obj_t *btn_matrix_part_up;
extern lv_obj_t *btn_matrix_part_down;
extern lv_obj_t *btn_matrix_part_mid;
extern lv_obj_t *status_bar;
extern lv_obj_t *label_mode_1;
extern lv_obj_t *label_mode_2;

extern lv_obj_t *array_mode_screen[2];

extern double prev_ans;
extern char current_screen;

uint32_t index_mode = 0;
uint32_t num_obj = 2;

void nav_cb(lv_event_t *event)
{
    lv_obj_t *btn = lv_event_get_target(event);

    lv_indev_t *index = lv_event_get_indev(event);
    lv_point_t coords;
    lv_indev_get_point(index, &coords);

    lv_area_t area;

    lv_obj_get_coords(btn, &area);

    double center_x = (area.x1 + area.x2) / 2;
    double center_y = (area.y1 + area.y2) / 2;

    coords.x = coords.x - center_x;
    coords.y = -(coords.y - center_y);

    double ang = (180 / M_PI) * atan2(coords.y, coords.x);

    if (ang < 0) ang += 360;

    // Left
    if (ang >= 135 && ang <= 225) {
        if (current_screen == 0) {
            lv_textarea_cursor_left(input_area);
        }

        if (current_screen == 1) {
            if (index_mode != 0) {
                lv_obj_set_state(array_mode_screen[index_mode], LV_STATE_DEFAULT, true);
                lv_obj_remove_state(array_mode_screen[index_mode], LV_STATE_FOCUSED);
                index_mode--;
                lv_obj_set_state(array_mode_screen[index_mode], LV_STATE_FOCUSED, true);
            }
        }
    }

    // Right
    if ((ang >= 315 && ang <= 360) || (ang <= 45 && ang >= 0)) {
        if (current_screen == 0) {
            lv_textarea_cursor_right(input_area);
        }

        if (current_screen == 1) {
            if (index_mode != 1) {
                lv_obj_set_state(array_mode_screen[index_mode], LV_STATE_DEFAULT, true);
                lv_obj_remove_state(array_mode_screen[index_mode], LV_STATE_FOCUSED);
                index_mode++;
                lv_obj_set_state(array_mode_screen[index_mode], LV_STATE_FOCUSED, true);
            }
        }
    }

    // Up
    if (ang >= 45 && ang <= 135) {
        if (current_screen != 0) return;
        if (lv_obj_get_scroll_top(input_area_container) >= 20) lv_obj_scroll_by(
            input_area_container, 0, 20, LV_ANIM_OFF);
        if (lv_obj_get_scroll_top(input_area_container) < 20) lv_obj_scroll_by(
            input_area_container, 0, lv_obj_get_scroll_top(input_area_container), LV_ANIM_OFF);
    }

    // Down
    if (ang >= 225 && ang <= 315) {
        if (current_screen != 0) return;
        if (lv_obj_get_scroll_bottom(input_area_container) >= 20) lv_obj_scroll_by(
            input_area_container, 0, -20, LV_ANIM_OFF);
        if (lv_obj_get_scroll_bottom(input_area_container) < 20) lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
    }
}

void btn_matrix_down_cb(lv_event_t *event)
{
    uint32_t *index = lv_event_get_param(event);
    lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
    if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "1") == 0) {
        lv_textarea_add_char(input_area, '1');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "2") == 0) {
        lv_textarea_add_char(input_area, '2');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "3") == 0) {
        lv_textarea_add_char(input_area, '3');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "4") == 0) {
        lv_textarea_add_char(input_area, '4');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "5") == 0) {
        lv_textarea_add_char(input_area, '5');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "6") == 0) {
        lv_textarea_add_char(input_area, '6');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "7") == 0) {
        lv_textarea_add_char(input_area, '7');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "8") == 0) {
        lv_textarea_add_char(input_area, '8');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "9") == 0) {
        lv_textarea_add_char(input_area, '9');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "0") == 0) {
        lv_textarea_add_char(input_area, '0');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), ".") == 0) {
        lv_textarea_add_char(input_area, '.');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "+") == 0) {
        lv_textarea_add_char(input_area, '+');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "-") == 0) {
        lv_textarea_add_char(input_area, '-');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "X") == 0) {
        lv_textarea_add_char(input_area, '*');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "/") == 0) {
        lv_textarea_add_char(input_area, '/');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "Pi") == 0) {
        lv_textarea_add_char(input_area, 'p');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "(") == 0) {
        lv_textarea_add_char(input_area, '(');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), ")") == 0) {
        lv_textarea_add_char(input_area, ')');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "DEL") == 0) {
        lv_textarea_delete_char(input_area);
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "=") == 0) {
        create_ans_label(interpret(lv_textarea_get_text(input_area)));
        create_line_ans();
        lv_obj_clear_state(input_area, LV_STATE_FOCUSED);
        create_input_area();
        lv_obj_align_to(input_area, line, LV_ALIGN_BOTTOM_MID, 0, 45);
        lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
        current_screen = 0;
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "AC") == 0) {
        lv_obj_delete(input_base);
        create_input_base();
        create_input_area_container();
        create_status_bar();
        create_input_area();
        current_screen = 0;
    }
}

void btn_matrix_up_cb(lv_event_t *event)
{
}

void btn_matrix_mid_cb(lv_event_t *event)
{
    uint32_t *index = lv_event_get_param(event);
    if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_mid, *index), "^") == 0) {
        lv_textarea_add_char(input_area, '^');
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_mid, *index), "MENU") == 0) {
        current_screen = 1;
        lv_obj_move_foreground(screen_menu);
        lv_obj_move_foreground(screen_menu_container);
        lv_obj_move_foreground(label_mode_1);
        lv_obj_move_foreground(label_mode_2);
        lv_obj_move_foreground(status_bar);
    }
}
