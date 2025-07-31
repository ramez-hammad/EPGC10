#include <lvgl.h>
#include <screen_graph.h>
#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

lv_obj_t *screen_graph_container;
lv_obj_t *grid;

extern lv_obj_t *status_bar;

int graph_drawn = 0;

void create_screen_graph_container(void)
{
    screen_graph_container = lv_obj_create(lv_screen_active());
    lv_obj_set_size(screen_graph_container, 320, 210);
    lv_obj_align(screen_graph_container, LV_ALIGN_TOP_MID, 0, 30);
    lv_obj_set_style_border_width(screen_graph_container, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(screen_graph_container, 0, LV_PART_MAIN);
    lv_obj_remove_flag(screen_graph_container, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_set_style_bg_color(screen_graph_container, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(screen_graph_container, LV_SCROLLBAR_MODE_OFF);
}

void create_screen_graph_grid(void)
{
    LV_DRAW_BUF_DEFINE_STATIC(draw_buf, 320, 210, LV_COLOR_FORMAT_ARGB8888);
    LV_DRAW_BUF_INIT_STATIC(draw_buf);

    grid = lv_canvas_create(screen_graph_container);
    lv_canvas_set_draw_buf(grid, &draw_buf);
    lv_obj_center(grid);

    lv_canvas_fill_bg(grid, lv_color_hex(0xffffff), LV_OPA_COVER);

    // Draw x-axis
    for (int x = 0; x < SCREEN_WIDTH_GRAPH; x++) {
        lv_canvas_set_px(grid, x, SCREEN_HEIGHT_GRAPH / 2, lv_color_hex(0x000000), LV_OPA_MAX);
        if (x % 5 == 0 || x == SCREEN_WIDTH_GRAPH - 1) {
            for (int y = (SCREEN_HEIGHT_GRAPH / 2) - 2; y <= (SCREEN_HEIGHT_GRAPH / 2) + 2; y++) {
                lv_canvas_set_px(grid, x, y, lv_color_hex(0x000000), LV_OPA_MAX);
            }

            if (x % 20 == 0) {
                for (int y = 0; y < SCREEN_HEIGHT_GRAPH; y++) {
                    lv_canvas_set_px(grid, x, y, lv_color_hex(0x808080), LV_OPA_MAX);
                }
            }
        }
    }

    // Draw y-axis
    for (int y = 0; y < SCREEN_HEIGHT_GRAPH; y++) {
        lv_canvas_set_px(grid, SCREEN_WIDTH_GRAPH / 2, y, lv_color_hex(0x000000), LV_OPA_MAX);
        if (y % 5 == 0 || y == SCREEN_HEIGHT_GRAPH - 1) {
            for (int x = (SCREEN_WIDTH_GRAPH / 2) - 2; x <= (SCREEN_WIDTH_GRAPH / 2) + 2; x++) {
                lv_canvas_set_px(grid, x, y, lv_color_hex(0x000000), LV_OPA_MAX);
            }


            if (y % 20 == 0) {
                for (int x = 0; x < SCREEN_WIDTH_GRAPH; x++) {
                    lv_canvas_set_px(grid, x, y + 5, lv_color_hex(0x808080), LV_OPA_MAX);
                    if (y + 5 == SCREEN_HEIGHT_GRAPH / 2) lv_canvas_set_px(grid, x, y + 5, lv_color_hex(0x000000), LV_OPA_MAX);
                }
            }
        }
    }
}

void create_screen_graph(void)
{
    create_screen_graph_container();
    create_screen_graph_grid();
}

void draw_graph()
{
}

void display_screen_graph(void)
{
    lv_obj_move_foreground(status_bar);
    lv_obj_move_foreground(screen_graph_container);
    if (!graph_drawn) draw_graph();
}
