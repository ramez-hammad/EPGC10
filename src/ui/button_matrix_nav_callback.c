#include <lvgl.h>
#include <math.h>
#include <button_matrix_nav_callback.h>
#include <text.h>
#include <input_area.h>

extern lv_obj_t *screen_menu_container;
extern lv_obj_t *input_area;
extern lv_obj_t *input_area_container;

extern char current_screen;

uint32_t col_index = 0;
uint32_t row_index = 0;

extern lv_obj_t *array_menu_screen[3][3];

extern lv_obj_t *array_graph_input_screen[];
extern int array_graph_input_screen_index;

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
        if (current_screen == 0 || current_screen == 2) {
            input_area_nav_left();
        }

        if (current_screen == 1) {
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
                        lv_obj_scroll_by(screen_menu_container, 0, lv_obj_get_scroll_top(screen_menu_container),
                                         LV_ANIM_OFF);
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
    }

    // Right
    if ((ang >= 315 && ang <= 360) || (ang <= 45 && ang >= 0)) {
        if (current_screen == 0 || current_screen == 2) {
            input_area_nav_right();
        }

        if (current_screen == 1) {
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

        if (current_screen == 2) {
            if (array_graph_input_screen_index == 0) return;
            lv_obj_clear_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_DEFAULT);
            array_graph_input_screen_index--;
            lv_obj_clear_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_FOCUSED);
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

        if (current_screen == 2) {
            if (array_graph_input_screen_index == 4) return;
            lv_obj_clear_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_FOCUSED);
            lv_obj_add_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_DEFAULT);
            array_graph_input_screen_index++;
            lv_obj_clear_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_DEFAULT);
            lv_obj_add_state(array_graph_input_screen[array_graph_input_screen_index], LV_STATE_FOCUSED);
        }
    }
}
