#include <lvgl.h>
#include <input_area.h>
#include <text.h>
#include <screen_menu.h>
#include <screen_settings.h>
#include <screen_graph.h>
#include <screen_graph_input.h>
#include <status_bar.h>

extern char alpha;
extern char shift;
extern char hyp;

extern char current_screen;

extern uint32_t col_index;
extern uint32_t row_index;
extern uint32_t num_menu_buttons;

extern lv_obj_t *screen_settings;

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

            refresh_status_bar();
            break;
        case 1:
            break;
        case 2:
            add_to_input_area("x\0");
            break;
        case 3:
            display_screen_menu();
            break;
        case 4:
            if (alpha) {
                alpha = 0;
            } else {
                alpha = 1;
                shift = 0;
                hyp = 0;
            }

            refresh_status_bar();
            break;
        case 5:
            if (alpha) alpha = 0;
            if (shift) {
                add_to_input_area("sqrt(\0");
            } else {
                add_to_input_area("^2\0");
            }
            break;
        case 6:
            add_to_input_area("^\0");
            break;
        case 7:
            switch (current_screen) {
                case SCREEN_ANGLE:
                case SCREEN_RESULT_FORMAT:
                    lv_obj_send_event(lv_menu_get_main_header_back_button(screen_settings), LV_EVENT_CLICKED, NULL);
                    current_screen = SCREEN_SETTINGS;
                    break;

                case SCREEN_SETTINGS:
                case SCREEN_GRAPH_INPUT:
                    display_screen_menu();
                    break;

                case SCREEN_GRAPH:
                    display_screen_graph_input();
                    break;

                case SCREEN_MENU:
                    display_screen_input();
                    break;
            }
            break;
    }
}
