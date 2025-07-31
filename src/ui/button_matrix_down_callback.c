#include <lvgl.h>
#include <input_area.h>
#include <status_bar.h>
#include <text.h>
#include <screen_graph.h>
#include <screen_graph_input.h>
#include <interpreter.h>

extern lv_obj_t *input_base;
extern lv_obj_t *input_area;
extern lv_obj_t *line;

extern char *input_buffer_main[];
extern char *output_buffer_main[];
extern int input_buffer_main_length;
extern int output_buffer_main_length;

extern char alpha;
extern char shift;

extern char current_screen;

extern uint32_t col_index;
extern uint32_t row_index;

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
                reset_buffer(input_buffer_main, &input_buffer_main_length);
                reset_buffer(output_buffer_main, &output_buffer_main_length);
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
            add_to_input_area(".\0");
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

            if (current_screen == 2) {
                display_screen_graph();
            }

            if (current_screen == 0) {
                create_ans_label(interpret(get_text(input_buffer_main, &input_buffer_main_length)));
                create_line_ans();
                lv_obj_clear_state(input_area, LV_STATE_FOCUSED);
                create_input_area();
                lv_obj_align_to(input_area, line, LV_ALIGN_BOTTOM_MID, 0, 45);
                lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
                reset_buffer(input_buffer_main, &input_buffer_main_length);
                reset_buffer(output_buffer_main, &output_buffer_main_length);
            }

            if (current_screen == 1) {
                // Back button pressed
                if (row_index == 0 && col_index == 0) {
                    display_screen_input();
                    current_screen = 0;
                }

                // Graph button pressed
                if (row_index == 0 && col_index == 1) {
                    display_screen_graph_input();
                    current_screen = 2;
                }
            }

            break;
    }
}
