#include <lvgl.h>
#include <math.h>
#include <button_matrix_nav_callback.h>
#include <text.h>
#include <input_area.h>
#include <screen_graph_input.h>
#include <screen_menu.h>
#include <screen_settings.h>
#include <screen_graph.h>

extern lv_obj_t *screen_menu_container;
extern lv_obj_t *input_area;
extern lv_obj_t *input_area_container;

extern char current_screen;

uint32_t col_index = 0;
uint32_t row_index = 0;

extern lv_obj_t *array_menu_screen[3][3];

extern lv_obj_t *array_graph_input_screen[];
extern int array_graph_input_screen_index;

extern lv_obj_t *array_settings_section[];
extern lv_obj_t *array_settings_angle_section[];
extern lv_obj_t *array_settings_result_format_section[];

extern char screen_settings_index;
extern char screen_settings_angle_index;
extern char screen_settings_result_format_index;

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
        if (current_screen == SCREEN_INPUT || current_screen == SCREEN_GRAPH_INPUT) {
            input_area_nav_left();
        }

        if (current_screen == SCREEN_MENU) {
            if (col_index > 0) {
                lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                col_index--;
                lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
            } else if (col_index == 0 && row_index > 0) {
                if ((row_index + 1) % 2 == 0) {
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                    col_index = COL_INDEX_LAST;
                    row_index--;
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                    if (row_index != 0) {
                        lv_obj_scroll_by(screen_menu_container, 0, 97, LV_ANIM_OFF);
                    } else {
                        lv_obj_scroll_by(screen_menu_container, 0, lv_obj_get_scroll_top(screen_menu_container), LV_ANIM_OFF);
                    }
                } else {
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                    col_index = COL_INDEX_LAST;
                    row_index--;
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                }
            }
        }

        if (current_screen == SCREEN_GRAPH) {
            const double dx = 0.1 * (x_max - x_min);

            x_max -= dx;
            x_min -= dx;

            create_screen_graph();
            draw_graph();
        }
    }

    // Right
    if ((ang >= 315 && ang <= 360) || (ang <= 45 && ang >= 0)) {
        if (current_screen == SCREEN_INPUT || current_screen == SCREEN_GRAPH_INPUT) {
            input_area_nav_right();
        }

        if (current_screen == SCREEN_MENU) {
            if (col_index < COL_INDEX_LAST) {
                lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                col_index++;
                lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
            } else if (col_index == COL_INDEX_LAST && row_index < ROW_INDEX_LAST) {
                if ((row_index + 1) % 2 == 0) {
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                    col_index = 0;
                    row_index++;
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                    lv_obj_scroll_by(screen_menu_container, 0, -97, LV_ANIM_OFF);
                } else {
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                    col_index = 0;
                    row_index++;
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                }
            }
        }

        if (current_screen == SCREEN_GRAPH) {
            const double dx = 0.1 * (x_max - x_min);

            x_max += dx;
            x_min += dx;

            create_screen_graph();
            draw_graph();
        }
    }

    // Up
    if (ang >= 45 && ang <= 135) {
        if (current_screen == SCREEN_INPUT) {
            if (lv_obj_get_scroll_top(input_area_container) >= 20)
                lv_obj_scroll_by(
                    input_area_container, 0, 20, LV_ANIM_OFF);
            if (lv_obj_get_scroll_top(input_area_container) < 20)
                lv_obj_scroll_by(
                    input_area_container, 0, lv_obj_get_scroll_top(input_area_container), LV_ANIM_OFF);
        }

        if (current_screen == SCREEN_MENU) {
            if (row_index > 0) {
                if ((row_index + 1) % 2 == 0) {
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                    row_index--;
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                    if (row_index != 0) {
                        lv_obj_scroll_by(screen_menu_container, 0, 97, LV_ANIM_OFF);
                    } else {
                        lv_obj_scroll_by(screen_menu_container, 0, lv_obj_get_scroll_top(screen_menu_container),
                                         LV_ANIM_OFF);
                    }
                } else {
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                    row_index--;
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                }
            }
        }

        if (current_screen == SCREEN_GRAPH_INPUT) {
            if (array_graph_input_screen_index == 0) return;
            lv_obj_clear_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_DEFAULT);
            array_graph_input_screen_index--;
            lv_obj_clear_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_FOCUSED);
        }

        if (current_screen == SCREEN_SETTINGS) {
            if (screen_settings_index == 0) return;
            lv_obj_clear_state(array_settings_section[screen_settings_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_settings_section[screen_settings_index], LV_STATE_DEFAULT);
            screen_settings_index--;
            lv_obj_clear_state(array_settings_section[screen_settings_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_settings_section[screen_settings_index], LV_STATE_FOCUSED);
        }

        if (current_screen == SCREEN_ANGLE) {
            if (screen_settings_angle_index == 0) return;
            lv_obj_clear_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_DEFAULT);
            screen_settings_angle_index--;
            lv_obj_clear_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_FOCUSED);
        }

        if (current_screen == SCREEN_RESULT_FORMAT) {
            if (screen_settings_result_format_index == 0) return;
            lv_obj_clear_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_DEFAULT);
            screen_settings_result_format_index--;
            lv_obj_clear_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_FOCUSED);
        }

        if (current_screen == SCREEN_GRAPH) {
            const double dy = 0.1 * (y_max - y_min);

            y_max += dy;
            y_min += dy;

            create_screen_graph();
            draw_graph();

            LV_LOG_USER("Y_MIN: %f, Y_MAX %f", y_min, y_max);
        }
    }

    // Down
    if (ang >= 225 && ang <= 315) {
        if (current_screen == SCREEN_INPUT) {
            if (lv_obj_get_scroll_bottom(input_area_container) >= 20)
                lv_obj_scroll_by(
                    input_area_container, 0, -20, LV_ANIM_OFF);
            if (lv_obj_get_scroll_bottom(input_area_container) < 20) lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
        }

        if (current_screen == SCREEN_MENU) {
            if (row_index < ROW_INDEX_LAST) {
                if ((row_index + 1) % 2 == 0) {
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                    row_index++;
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                    lv_obj_scroll_by(screen_menu_container, 0, -97, LV_ANIM_OFF);
                } else {
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_DEFAULT, true);
                    lv_obj_remove_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED);
                    row_index++;
                    lv_obj_set_state(array_menu_screen[row_index][col_index], LV_STATE_FOCUSED, true);
                }
            }
        }

        if (current_screen == SCREEN_GRAPH_INPUT) {
            if (array_graph_input_screen_index == 4) return;
            lv_obj_clear_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_DEFAULT);
            array_graph_input_screen_index++;
            lv_obj_clear_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_FOCUSED);
        }

        if (current_screen == SCREEN_SETTINGS) {
            if (screen_settings_index == 1) return;
            lv_obj_clear_state(array_settings_section[screen_settings_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_settings_section[screen_settings_index], LV_STATE_DEFAULT);
            screen_settings_index++;
            lv_obj_clear_state(array_settings_section[screen_settings_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_settings_section[screen_settings_index], LV_STATE_FOCUSED);
        }

        if (current_screen == SCREEN_ANGLE) {
            if (screen_settings_angle_index == 2) return;
            lv_obj_clear_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_DEFAULT);
            screen_settings_angle_index++;
            lv_obj_clear_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_settings_angle_section[screen_settings_angle_index], LV_STATE_FOCUSED);
        }

        if (current_screen == SCREEN_RESULT_FORMAT) {
            if (screen_settings_result_format_index == 2) return;
            lv_obj_clear_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_DEFAULT);
            screen_settings_result_format_index++;
            lv_obj_clear_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_settings_result_format_section[screen_settings_result_format_index], LV_STATE_FOCUSED);
        }

        if (current_screen == SCREEN_GRAPH) {
            const double dy = 0.1 * (y_max - y_min);

            y_max -= dy;
            y_min -= dy;

            create_screen_graph();
            draw_graph();

            LV_LOG_USER("Y_MIN: %f, Y_MAX %f", y_min, y_max);
        }
    }
}
