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

char *input_buffer[MAXLEN_INPUT + 1];
char *output_buffer[MAXLEN_INPUT + 1];

int input_buffer_length = 0;
int output_buffer_length = 0;

extern char shift;
extern char alpha;

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
                        lv_obj_scroll_by(screen_menu_container, 0, lv_obj_get_scroll_top(screen_menu_container),
                                         LV_ANIM_OFF);
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
            if (lv_obj_get_scroll_top(input_area_container) >= 20)
                lv_obj_scroll_by(
                    input_area_container, 0, 20, LV_ANIM_OFF);
            if (lv_obj_get_scroll_top(input_area_container) < 20)
                lv_obj_scroll_by(
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
                        lv_obj_scroll_by(screen_menu_container, 0, lv_obj_get_scroll_top(screen_menu_container),
                                         LV_ANIM_OFF);
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
            if (lv_obj_get_scroll_bottom(input_area_container) >= 20)
                lv_obj_scroll_by(
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
    switch (*index) {
        case 0:
            if (alpha) {
                alpha = 0;
                add_to_input_area("A\0");
            }
            break;
        case 1:
            if (alpha) {
                alpha = 0;
                add_to_input_area("B\0");
            } else {
                add_to_input_area("log(\0");
            }
            break;
        case 2:
            if (alpha) {
                alpha = 0;
                add_to_input_area("C\0");
            } else {
                add_to_input_area("ln(\0");
            }
            break;
        case 3:
            if (alpha) {
                alpha = 0;
                add_to_input_area("D\0");
            } else if (shift) {
                shift = 0;
                add_to_input_area("arcsin(\0");
            } else {
                add_to_input_area("sin(\0");
            }
            break;
        case 4:
            if (alpha) {
                alpha = 0;
                add_to_input_area("E\0");
            } else if (shift) {
                shift = 0;
                add_to_input_area("arccos(\0");
            } else {
                add_to_input_area("cos(\0");
            }
            break;
        case 5:
            if (alpha) {
                alpha = 0;
                add_to_input_area("F\0");
            } else if (shift) {
                shift = 0;
                add_to_input_area("arctan(\0");
            } else {
                add_to_input_area("tan(\0");
            }
            break;
        case 6:
            if (alpha) {
                alpha = 0;
                add_to_input_area("G\0");
            }
            break;
        case 7:
            if (alpha) {
                alpha = 0;
                add_to_input_area("H\0");
            }
            break;
        case 8:
            if (alpha) {
                alpha = 0;
                add_to_input_area("I\0");
            } else {
                add_to_input_area("(\0");
            }
            break;
        case 9:
            if (alpha) {
                alpha = 0;
                add_to_input_area("J\0");
            } else {
                add_to_input_area(")\0");
            }
            break;
        case 10:
            if (alpha) {
                alpha = 0;
                add_to_input_area("K\0");
            }
            break;
        case 11:
            if (alpha) {
                alpha = 0;
                add_to_input_area("L\0");
            }
            break;
        case 12:
            if (alpha) {
                alpha = 0;
                add_to_input_area("M\0");
            } else {
                add_to_input_area("7\0");
            }
            break;
        case 13:
            if (alpha) {
                alpha = 0;
                add_to_input_area("N\0");
            } else {
                add_to_input_area("8\0");
            }
            break;
        case 14:
            if (alpha) {
                alpha = 0;
                add_to_input_area("O\0");
            } else {
                add_to_input_area("9\0");
            }
            break;
        case 15:
            if (alpha) {
                alpha = 0;
                add_to_input_area("P\0");
            } else {
                if (shift) shift = 0;
                if (alpha) alpha = 0;
                delete_from_input_area();
            }
            break;
        case 16:
            if (alpha) {
                alpha = 0;
                add_to_input_area("Q\0");
            } else {
                if (shift) shift = 0;
                if (alpha) alpha = 0;
                lv_obj_delete(input_base);
                create_input_base();
                create_input_area_container();
                create_status_bar();
                create_input_area();
                reset_input_buffer(input_buffer, &input_buffer_length);
                reset_input_buffer(output_buffer, &output_buffer_length);
                current_screen = 0;
            }
            break;
        case 17:
            if (alpha) {
                alpha = 0;
                add_to_input_area("R\0");
            } else {
                add_to_input_area("4\0");
            }
            break;
        case 18:
            if (alpha) {
                alpha = 0;
                add_to_input_area("S\0");
            } else {
                add_to_input_area("5\0");
            }
            break;
        case 19:
            if (alpha) {
                alpha = 0;
                add_to_input_area("T\0");
            } else {
                add_to_input_area("6\0");
            }
            break;
        case 20:
            if (alpha) {
                alpha = 0;
                add_to_input_area("U\0");
            } else {
                add_to_input_area("*\0");
            }
            break;
        case 21:
            if (alpha) {
                alpha = 0;
                add_to_input_area("V\0");
            } else {
                add_to_input_area("/\0");
            }
            break;
        case 22:
            if (alpha) {
                alpha = 0;
                add_to_input_area("W\0");
            } else {
                add_to_input_area("1\0");
            }
            break;
        case 23:
            if (alpha) {
                alpha = 0;
                add_to_input_area("X\0");
            } else {
                add_to_input_area("2\0");
            }
            break;
        case 24:
            if (alpha) {
                alpha = 0;
                add_to_input_area("Y\0");
            } else {
                add_to_input_area("3\0");
            }
            break;
        case 25:
            if (alpha) {
                alpha = 0;
                add_to_input_area("Z\0");
            } else {
                add_to_input_area("+\0");
            }
            break;
        case 26:
            if (alpha) alpha = 0;
            if (shift) shift = 0;
            add_to_input_area("-\0");
            break;
        case 27:
            if (alpha) alpha = 0;
            if (shift) shift = 0;
            add_to_input_area("0\0");
            break;
        case 28:
            if (alpha) alpha = 0;
            if (shift) shift = 0;
            break;
        case 29:
            if (alpha) alpha = 0;
            if (shift) shift = 0;
            add_to_input_area("p\0");
            break;
        case 30:
            if (alpha) alpha = 0;
            if (shift) shift = 0;
            break;
        case 31:
            if (alpha) alpha = 0;
            if (shift) shift = 0;
            if (current_screen == 0) {
                create_ans_label(interpret(get_text(input_buffer, &input_buffer_length)));
                create_line_ans();
                lv_obj_clear_state(input_area, LV_STATE_FOCUSED);
                create_input_area();
                lv_obj_align_to(input_area, line, LV_ALIGN_BOTTOM_MID, 0, 45);
                lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
                reset_input_buffer(input_buffer, &input_buffer_length);
                reset_input_buffer(output_buffer, &output_buffer_length);
            }

            if (current_screen == 1) {
                // Back button pressed
                if (row_index == 0 && col_index == 0) {
                    display_screen_input();
                    current_screen = 0;
                }
            }
            break;
    }
}

void btn_matrix_up_cb(lv_event_t *event)
{
}

void btn_matrix_mid_cb(lv_event_t *event)
{
    uint32_t *index = lv_event_get_param(event);

    switch (*index) {
        case 0:
            if (shift) {
                shift = 0;
            } else {
                shift = 1;
                alpha = 0;
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            current_screen = 1;
            num_obj = 0;
            col_index = 0;
            row_index = 0;

            display_screen_menu();
            break;
        case 4:
            if (alpha) {
                alpha = 0;
            } else {
                alpha = 1;
                shift = 0;
            }
            break;
        case 5:
            add_to_input_area("^2\0");
            break;
        case 6:
            add_to_input_area("^\0");
            break;
        case 7:
            break;
    }
}
