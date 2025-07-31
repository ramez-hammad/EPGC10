#include <lvgl.h>
#include <input_area.h>
#include <text.h>
#include <screen_menu.h>

extern char alpha;
extern char shift;

extern char current_screen;

extern uint32_t col_index;
extern uint32_t row_index;
extern uint32_t num_obj;

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
            break;
    }
}
