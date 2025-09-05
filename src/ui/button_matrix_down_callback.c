#include <lvgl.h>
#include <input_area.h>
#include <status_bar.h>
#include <text.h>
#include <screen_graph.h>
#include <screen_graph_input.h>
#include <interpreter.h>
#include <screen_menu.h>
#include <screen_settings.h>
#include <string.h>
#include <toolbox_popup.h>
#include <var_popup.h>
#include <error_popup.h>
#include <error.h>
#include <lexer.h>
#include <parser.h>
#include <evaluator.h>

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

extern uint32_t input_buffer_main_current_pos;

extern lv_obj_t *array_settings_section[];
extern lv_obj_t *array_settings_angle_section[];
extern lv_obj_t *array_settings_result_format_section[];

extern char screen_settings_index;
extern char screen_settings_angle_index;
extern char screen_settings_result_format_index;

extern char deg_rad;
extern char *display_format;

char hyp;

void btn_matrix_down_cb(lv_event_t *event)
{
    uint32_t *index = lv_event_get_param(event);
    lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
    switch (*index) {
        case 0:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;

            if (hyp) {
                hyp = 0;
            } else if (alpha) {
                alpha = 0;
                add_to_input_area("A\0");
            } else {
                hyp = 1;
            }

            refresh_status_bar();

            break;
        case 1:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("B\0");
            } else {
                add_to_input_area("log(\0");
            }
            break;
        case 2:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("C\0");
            } else {
                add_to_input_area("ln(\0");
            }
            break;
        case 3:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("D\0");
            } else if (shift) {
                shift = 0;

                if (hyp) {
                    hyp = 0;
                    add_to_input_area("arcsinh(\0");
                } else {
                    add_to_input_area("arcsin(\0");
                }
            } else {
                if (hyp) {
                    hyp = 0;
                    add_to_input_area("sinh(\0");
                } else {
                    add_to_input_area("sin(\0");
                }
            }
            break;
        case 4:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("E\0");
            } else if (shift) {
                shift = 0;

                if (hyp) {
                    hyp = 0;
                    add_to_input_area("arccosh(\0");
                } else {
                    add_to_input_area("arccos(\0");
                }
            } else {
                if (hyp) {
                    hyp = 0;
                    add_to_input_area("cosh(\0");
                } else {
                    add_to_input_area("cos(\0");
                }
            }
            break;
        case 5:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("F\0");
            } else if (shift) {
                shift = 0;

                if (hyp) {
                    hyp = 0;
                    add_to_input_area("arctanh(\0");
                } else {
                    add_to_input_area("arctan(\0");
                }
            } else {
                if (hyp) {
                    hyp = 0;
                    add_to_input_area("tanh(\0");
                } else {
                    add_to_input_area("tan(\0");
                }
            }
            break;
        case 6:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("G\0");
            } else {
                add_to_input_area("e");
                add_to_input_area("^");
            }
            break;
        case 7:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("H\0");
            } else {
                add_to_input_area("*");
                add_to_input_area("10");
                add_to_input_area("^");
            }
            break;
        case 8:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("I\0");
            } else {
                add_to_input_area("(\0");
            }
            break;
        case 9:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("J\0");
            } else {
                add_to_input_area(")\0");
            }
            break;
        case 10:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("K\0");
            }
            break;
        case 11:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("L\0");
            } else {
                display_var_popup();
            }
            break;
        case 12:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("M\0");
            } else {
                add_to_input_area("7\0");
            }
            break;
        case 13:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("N\0");
            } else {
                add_to_input_area("8\0");
            }
            break;
        case 14:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("O\0");
            } else {
                add_to_input_area("9\0");
            }
            break;
        case 15:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
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
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("Q\0");
            } else {
                if (current_screen != SCREEN_INPUT) break;
                if (shift) shift = 0;
                if (alpha) alpha = 0;
                if (hyp) hyp = 0;
                lv_obj_delete(input_base);
                create_input_base();
                create_status_bar();
                create_input_area();
                reset_buffer(input_buffer_main, &input_buffer_main_length);
                reset_buffer(output_buffer_main, &output_buffer_main_length);
                current_screen = SCREEN_INPUT;
            }
            break;
        case 17:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("R\0");
            } else {
                add_to_input_area("4\0");
            }
            break;
        case 18:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("S\0");
            } else {
                add_to_input_area("5\0");
            }
            break;
        case 19:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("T\0");
            } else {
                add_to_input_area("6\0");
            }
            break;
        case 20:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("U\0");
            } else {
                add_to_input_area("*\0");
            }
            break;
        case 21:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("V\0");
            } else {
                add_to_input_area("/\0");
            }
            break;
        case 22:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("W\0");
            } else {
                add_to_input_area("1\0");
            }
            break;
        case 23:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("X\0");
            } else {
                add_to_input_area("2\0");
            }
            break;
        case 24:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) {
                alpha = 0;
                add_to_input_area("Y\0");
            } else {
                add_to_input_area("3\0");
            }
            break;
        case 25:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT && current_screen != SCREEN_GRAPH || toolbox_open) break;

            if (current_screen == SCREEN_GRAPH) {
                // Zoom in

                y_min = 0.7 * y_min;
                y_max = 0.7 * y_max;

                x_min = 0.7 * x_min;
                x_max = 0.7 * x_max;

                create_screen_graph();
                draw_graph();

                break;
            }

            if (alpha) {
                alpha = 0;
                add_to_input_area("Z\0");
            } else {
                add_to_input_area("+\0");
            }

            break;
        case 26:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT && current_screen != SCREEN_GRAPH || toolbox_open) break;

            if (current_screen == SCREEN_GRAPH) {
                // Zoom in
                y_min = 1.428571 * y_min;
                y_max = 1.428571 * y_max;

                x_min = 1.428571 * x_min;
                x_max = 1.428571 * x_max;

                create_screen_graph();
                draw_graph();

                break;
            }

            if (alpha) alpha = 0;
            if (shift) shift = 0;
            add_to_input_area("-\0");
            break;
        case 27:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) alpha = 0;
            if (shift) shift = 0;
            add_to_input_area("0\0");
            break;
        case 28:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;

            if (alpha) {
                alpha = 0;
                add_to_input_area("!\0");
            } else if (shift) {
                shift = 0;
            } else {
                add_to_input_area(".\0");
            }

            break;
        case 29:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) alpha = 0;
            if (shift) shift = 0;

            add_to_input_area("p\0");

            break;
        case 30:
            if (current_screen != SCREEN_INPUT && current_screen != SCREEN_GRAPH_INPUT || toolbox_open) break;
            if (alpha) alpha = 0;
            if (shift) shift = 0;

            add_to_input_area("Ans\0");

            break;
        case 31:
            if (alpha) alpha = 0;
            if (shift) shift = 0;
            if (hyp) hyp = 0;

            if (current_screen == SCREEN_RESULT_FORMAT) {
                // Normal
                if (screen_settings_result_format_index == 0) display_format = "NORMAL";
                if (screen_settings_result_format_index == 1) display_format = "SCI";
                if (screen_settings_result_format_index == 2) display_format = "ENG";

                refresh_status_bar();
            }

            if (current_screen == SCREEN_ANGLE) {
                // Degrees
                if (screen_settings_angle_index == 0) deg_rad = 0;

                // Radians
                if (screen_settings_angle_index == 1) deg_rad = 1;

                // Gradians
                if (screen_settings_angle_index == 2) deg_rad = 2;

                refresh_status_bar();
            }

            if (current_screen == SCREEN_SETTINGS) {
                // Angle button pressed
                if (screen_settings_index == 0) {
                    lv_obj_send_event(array_settings_section[screen_settings_index], LV_EVENT_CLICKED, NULL);
                    current_screen = SCREEN_ANGLE;
                }

                // Result format button pressed
                if (screen_settings_index == 1) {
                    lv_obj_send_event(array_settings_section[screen_settings_index], LV_EVENT_CLICKED, NULL);
                    current_screen = SCREEN_RESULT_FORMAT;
                }
            }

            if (current_screen == SCREEN_GRAPH_INPUT) {
                if (toolbox_open) {
                    switch (toolbox_1_index) {
                        case 0:
                            add_to_input_area("abs(");
                            display_screen_graph_input();
                            lv_obj_add_state(get_input_area(), LV_STATE_FOCUSED);
                            toolbox_open = false;
                            break;
                    }
                    break;
                }

                if (var_popup_open) {
                    char var = *get_text(input_buffer_var_1, input_buffer_var_1_length);

                    double val = interpret(get_text(input_buffer_var_2, input_buffer_var_2_length));

                    if (error_present) {
                        display_error_popup();
                        error_present = 0;
                    } else if (!(var >= 65 && var <= 90)) {
                        // If var is not A-Z
                        display_error_popup();
                    } else {
                        switch (var) {
                            case 'A':
                                A = val;
                                break;
                            case 'B':
                                B = val;
                                break;
                            case 'C':
                                C = val;
                                break;
                            case 'D':
                                D = val;
                                break;
                            case 'E':
                                E = val;
                                break;
                            case 'F':
                                F = val;
                                break;
                            case 'G':
                                G = val;
                                break;
                            case 'H':
                                H = val;
                                break;
                            case 'I':
                                I_VAL = val;
                                break;
                            case 'J':
                                J = val;
                                break;
                            case 'K':
                                K = val;
                                break;
                            case 'L':
                                L = val;
                                break;
                            case 'M':
                                M = val;
                                break;
                            case 'N':
                                N = val;
                                break;
                            case 'O':
                                O = val;
                                break;
                            case 'P':
                                P = val;
                                break;
                            case 'Q':
                                Q = val;
                                break;
                            case 'R':
                                R = val;
                                break;
                            case 'S':
                                S = val;
                                break;
                            case 'T':
                                T = val;
                                break;
                            case 'U':
                                U = val;
                                break;
                            case 'V':
                                V = val;
                                break;
                            case 'W':
                                W = val;
                                break;
                            case 'X':
                                X = val;
                                break;
                            case 'Y':
                                Y = val;
                                break;
                            case 'Z':
                                Z = val;
                                break;
                        }

                        lv_obj_set_state(input_area_var_2, LV_STATE_DEFAULT, true);
                        lv_obj_remove_state(input_area_var_2, LV_STATE_FOCUSED);

                        lv_obj_add_state(input_area_var_1, LV_STATE_FOCUSED);

                        lv_obj_move_background(var_popup_container);

                        var_popup_open = false;

                        var_popup_index = 0;

                        lv_obj_set_state(get_input_area(), LV_STATE_FOCUSED, true);
                    }

                    break;
                }

                display_screen_graph();
            }

            if (current_screen == SCREEN_INPUT) {
                if (toolbox_open) {
                    switch (toolbox_1_index) {
                        case 0:
                            add_to_input_area("abs(");
                            display_screen_input();
                            lv_obj_add_state(get_input_area(), LV_STATE_FOCUSED);
                            toolbox_open = false;
                            break;
                    }
                    break;
                }

                if (var_popup_open) {
                    char var = *get_text(input_buffer_var_1, input_buffer_var_1_length);

                    double val = interpret(get_text(input_buffer_var_2, input_buffer_var_2_length));

                    if (error_present) {
                        lv_label_set_text(error_label, "Your input is not valid");
                        display_error_popup();
                        error_present = 0;
                    } else if (!(var >= 65 && var <= 90)) {
                        // If var is not A-Z
                        lv_label_set_text(error_label, "Your input is not valid");
                        display_error_popup();
                        error_present = 0;
                    } else {
                        switch (var) {
                            case 'A':
                                A = val;
                                break;
                            case 'B':
                                B = val;
                                break;
                            case 'C':
                                C = val;
                                break;
                            case 'D':
                                D = val;
                                break;
                            case 'E':
                                E = val;
                                break;
                            case 'F':
                                F = val;
                                break;
                            case 'G':
                                G = val;
                                break;
                            case 'H':
                                H = val;
                                break;
                            case 'I':
                                I_VAL = val;
                                break;
                            case 'J':
                                J = val;
                                break;
                            case 'K':
                                K = val;
                                break;
                            case 'L':
                                L = val;
                                break;
                            case 'M':
                                M = val;
                                break;
                            case 'N':
                                N = val;
                                break;
                            case 'O':
                                O = val;
                                break;
                            case 'P':
                                P = val;
                                break;
                            case 'Q':
                                Q = val;
                                break;
                            case 'R':
                                R = val;
                                break;
                            case 'S':
                                S = val;
                                break;
                            case 'T':
                                T = val;
                                break;
                            case 'U':
                                U = val;
                                break;
                            case 'V':
                                V = val;
                                break;
                            case 'W':
                                W = val;
                                break;
                            case 'X':
                                X = val;
                                break;
                            case 'Y':
                                Y = val;
                                break;
                            case 'Z':
                                Z = val;
                                break;
                        }

                        lv_obj_set_state(input_area_var_2, LV_STATE_DEFAULT, true);
                        lv_obj_remove_state(input_area_var_2, LV_STATE_FOCUSED);

                        lv_obj_add_state(input_area_var_1, LV_STATE_FOCUSED);

                        lv_obj_move_background(var_popup_container);

                        var_popup_open = false;

                        var_popup_index = 0;

                        lv_obj_set_state(get_input_area(), LV_STATE_FOCUSED, true);
                    }

                    break;
                }

                char *expr = get_text(input_buffer_main, input_buffer_main_length);
                if (strcmp(expr, "") != 0) {
                    double ans = interpret(expr);
                    if (!error_present) {
                        create_ans_label(ans);
                        create_line_ans();
                        lv_obj_clear_state(input_area, LV_STATE_FOCUSED);
                        create_input_area();
                        lv_obj_align_to(input_area, line, LV_ALIGN_BOTTOM_MID, 0, 45);
                        lv_obj_scroll_to_view(input_area, LV_ANIM_OFF);
                        reset_buffer(input_buffer_main, &input_buffer_main_length);
                        reset_buffer(output_buffer_main, &output_buffer_main_length);
                    } else {
                        lv_label_set_text(error_label, error_message);
                        display_error_popup();
                        error_present = 0;
                    }
                }
            }

            if (current_screen == SCREEN_MENU) {
                if (toolbox_open) toolbox_open = false;
                if (var_popup_open) var_popup_open = false;

                // Back button pressed
                if (row_index == 0 && col_index == 0) {
                    display_screen_input();
                    lv_obj_add_state(get_input_area(), LV_STATE_FOCUSED);
                }

                // Graph button pressed
                if (row_index == 0 && col_index == 1) {
                    display_screen_graph_input();
                    lv_obj_add_state(get_input_area(), LV_STATE_FOCUSED);
                }

                // Settings button pressed
                if (row_index == 0 && col_index == 2) {
                    display_screen_settings();
                }
            }

            break;
    }
    refresh_status_bar();
}
