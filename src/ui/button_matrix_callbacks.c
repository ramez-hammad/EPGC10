#include <lvgl.h>
#include <string.h>
#include <ui.h>
#include <interpreter.h>

extern lv_obj_t *input_base;
extern lv_obj_t *line;
extern lv_obj_t *input_area;
extern lv_obj_t *input_area_container;
extern lv_obj_t *btn_matrix_part_up;
extern lv_obj_t *btn_matrix_part_down;
extern lv_obj_t *btn_matrix_part_mid;
extern double prev_ans;
extern char current_screen;

void nav_cb_right(lv_event_t *event)
{
    if (current_screen != 0) return;
    lv_textarea_cursor_right(input_area);
}

void nav_cb_left(lv_event_t *event)
{
    if (current_screen != 0) return;
    lv_textarea_cursor_left(input_area);
}

void nav_cb_up(lv_event_t *event)
{
    if (current_screen != 0) return;
    if (lv_obj_get_scroll_top(input_area_container) >= 20) lv_obj_scroll_by(input_area_container, 0, 20, LV_ANIM_OFF);
    if (lv_obj_get_scroll_top(input_area_container) < 20) lv_obj_scroll_by(input_area_container, 0, lv_obj_get_scroll_top(input_area_container), LV_ANIM_OFF);
}

void nav_cb_down(lv_event_t *event)
{
    if (current_screen != 0) return;
    if (lv_obj_get_scroll_bottom(input_area_container) >= 20) lv_obj_scroll_by(input_area_container, 0, -20, LV_ANIM_OFF);
    if (lv_obj_get_scroll_bottom(input_area_container) < 20) lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
}

void btn_matrix_down_cb(lv_event_t *event)
{
    uint32_t *index = lv_event_get_param(event);
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
    }
}
