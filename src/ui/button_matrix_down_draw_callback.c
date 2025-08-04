#include <lvgl.h>
#include <ui.h>

void btn_matrix_down_draw_cb(lv_event_t *event)
{
    lv_draw_task_t * draw_task = lv_event_get_draw_task(event);
    lv_draw_dsc_base_t * base_dsc = (lv_draw_dsc_base_t *)lv_draw_task_get_draw_dsc(draw_task);

    if(base_dsc->part == LV_PART_ITEMS) {
        if(base_dsc->id1 == 15) {
            lv_draw_fill_dsc_t * fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);

            if(fill_draw_dsc) {
                fill_draw_dsc->color = lv_color_hex(BG_COLOR_MENU_SELECTED);
            }

            lv_draw_label_dsc_t * label_draw_dsc = lv_draw_task_get_label_dsc(draw_task);
            if(label_draw_dsc) {
                label_draw_dsc->color = lv_color_hex(0xffffff);
            }
        }

        if(base_dsc->id1 == 16) {
            lv_draw_fill_dsc_t * fill_draw_dsc = lv_draw_task_get_fill_dsc(draw_task);

            if(fill_draw_dsc) {
                fill_draw_dsc->color = lv_color_hex(BG_COLOR_MENU_SELECTED);
            }

            lv_draw_label_dsc_t * label_draw_dsc = lv_draw_task_get_label_dsc(draw_task);
            if(label_draw_dsc) {
                label_draw_dsc->color = lv_color_hex(0xffffff);
            }
        }
    }
}
