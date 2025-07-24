#include <lvgl.h>
#include <input_area.h>
#include <string.h>
#include <interpreter.h>
#include <math.h>
#include <button_matrix_callbacks.h>
#include <text.h>
#include <status_bar.h>
#include <screen_menu.h>

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
extern lv_obj_t *back_button_menu;
extern lv_obj_t *graph_button_menu;


extern double prev_ans;
extern char current_screen;

uint32_t col_index = 0;
uint32_t row_index = 0;
uint32_t num_obj;

extern lv_obj_t *array_mode_screen[3][3];

char* input_buffer[MAXLEN_INPUT + 1];

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
            if (col_index > 0) {
                lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                col_index--;
                lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
            } else if (col_index == 0 && row_index > 0) {
                if ((row_index + 1) % 2 == 0) {
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                    col_index = COL_INDEX_LAST;
                    row_index--;
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                    if (row_index != 0) {
                        lv_obj_scroll_by(screen_menu_container, 0, 97, LV_ANIM_OFF);
                    } else {
                        lv_obj_scroll_by(screen_menu_container, 0, lv_obj_get_scroll_top(screen_menu_container), LV_ANIM_OFF);
                    }
                } else {
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                    col_index = COL_INDEX_LAST;
                    row_index--;
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                }
            }
        }
    }

    // Right
    if ((ang >= 315 && ang <= 360) || (ang <= 45 && ang >= 0)) {
        if (current_screen == 0) {
            lv_textarea_cursor_right(input_area);
        }

        if (current_screen == 1) {
            if (col_index < COL_INDEX_LAST) {
                lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                col_index++;
                lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
            } else if (col_index == COL_INDEX_LAST && row_index < ROW_INDEX_LAST) {
                if ((row_index + 1) % 2 == 0) {
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                    col_index = 0;
                    row_index++;
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                    lv_obj_scroll_by(screen_menu_container, 0, -97, LV_ANIM_OFF);
                } else {
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                    col_index = 0;
                    row_index++;
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                }
            }
        }
    }

    // Up
    if (ang >= 45 && ang <= 135) {
        if (current_screen == 0) {
            if (lv_obj_get_scroll_top(input_area_container) >= 20) lv_obj_scroll_by(
                input_area_container, 0, 20, LV_ANIM_OFF);
            if (lv_obj_get_scroll_top(input_area_container) < 20) lv_obj_scroll_by(
                input_area_container, 0, lv_obj_get_scroll_top(input_area_container), LV_ANIM_OFF);
        }

        if (current_screen == 1) {
            if (row_index > 0) {
                if ((row_index + 1) % 2 == 0) {
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                    row_index--;
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                    if (row_index != 0) {
                        lv_obj_scroll_by(screen_menu_container, 0, 97, LV_ANIM_OFF);
                    } else {
                        lv_obj_scroll_by(screen_menu_container, 0, lv_obj_get_scroll_top(screen_menu_container), LV_ANIM_OFF);
                    }
                } else {
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                    row_index--;
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                }
            }
        }
    }

    // Down
    if (ang >= 225 && ang <= 315) {
        if (current_screen == 0) {
            if (lv_obj_get_scroll_bottom(input_area_container) >= 20) lv_obj_scroll_by(
                input_area_container, 0, -20, LV_ANIM_OFF);
            if (lv_obj_get_scroll_bottom(input_area_container) < 20) lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
        }

        if (current_screen == 1) {
            if (row_index < ROW_INDEX_LAST) {
                if ((row_index + 1) % 2 == 0) {
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                    row_index++;
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                    lv_obj_scroll_by(screen_menu_container, 0, -97, LV_ANIM_OFF);
                } else {
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED);
                    row_index++;
                    lv_obj_set_state(array_mode_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                }
            }
        }
    }
}

void btn_matrix_down_cb(lv_event_t *event)
{
    uint32_t *index = lv_event_get_param(event);
    lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
    if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "1") == 0) {
        append_text(input_buffer, "1\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "2") == 0) {
        append_text(input_buffer, "2\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "3") == 0) {
        append_text(input_buffer, "3\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "4") == 0) {
        append_text(input_buffer, "4\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "5") == 0) {
        append_text(input_buffer, "5\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "6") == 0) {
        append_text(input_buffer, "6\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "7") == 0) {
        append_text(input_buffer, "7\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "8") == 0) {
        append_text(input_buffer, "8\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "9") == 0) {
        append_text(input_buffer, "9\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "0") == 0) {
        append_text(input_buffer, "0\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), ".") == 0) {
        append_text(input_buffer, ".\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "+") == 0) {
        append_text(input_buffer, "+\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "-") == 0) {
        append_text(input_buffer, "-\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "X") == 0) {
        append_text(input_buffer, "*\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "/") == 0) {
        append_text(input_buffer, "/\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "Pi") == 0) {
        append_text(input_buffer, "p\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "(") == 0) {
        append_text(input_buffer, "(\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), ")") == 0) {
        append_text(input_buffer, ")\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "sin") == 0) {
        append_text(input_buffer, "sin(\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "cos") == 0) {
        append_text(input_buffer, "cos(\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "tan") == 0) {
        append_text(input_buffer, "tan(\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "log") == 0) {
        append_text(input_buffer, "log(\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "ln") == 0) {
        append_text(input_buffer, "ln(\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "DEL") == 0) {
        delete_text(input_buffer);
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "=") == 0) {
        create_ans_label(interpret(lv_textarea_get_text(input_area)));
        create_line_ans();
        lv_obj_clear_state(input_area, LV_STATE_FOCUSED);
        create_input_area();
        lv_obj_align_to(input_area, line, LV_ALIGN_BOTTOM_MID, 0, 45);
        lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
        reset_input_buffer(input_buffer);
        current_screen = 0;
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_down, *index), "AC") == 0) {
        lv_obj_delete(input_base);
        create_input_base();
        create_input_area_container();
        create_status_bar();
        create_input_area();
        reset_input_buffer(input_buffer);
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
        append_text(input_buffer, "^\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_mid, *index), "MENU") == 0) {
        current_screen = 1;
        num_obj = 0;
        col_index = 0;
        row_index = 0;

        display_screen_menu();
    } else if (strcmp(lv_buttonmatrix_get_button_text(btn_matrix_part_mid, *index), "x^2") == 0) {
        append_text(input_buffer, "^2\0");
        lv_textarea_set_text(input_area, get_text(input_buffer));
    }
}
