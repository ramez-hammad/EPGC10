#include <ctype.h>
#include <lvgl.h>
#include <screen_graph.h>
#include <math.h>
#include <stdlib.h>
#include <interpreter.h>
#include <string.h>
#include <text.h>

lv_obj_t *screen_graph_container;
lv_obj_t *grid;

extern lv_obj_t *status_bar;

extern char current_screen;

extern double x_value;

extern char deg_rad;

int graph_drawn = 0;

double x_min = -2 * M_PI;
double x_max = 2 * M_PI;
double y_min = -1.0;
double y_max = 1.0;

extern char *input_buffer_y_1[MAXLEN_INPUT + 1];
extern char *input_buffer_y_2[MAXLEN_INPUT + 1];
extern char *input_buffer_y_3[MAXLEN_INPUT + 1];
extern char *input_buffer_y_4[MAXLEN_INPUT + 1];
extern char *input_buffer_y_5[MAXLEN_INPUT + 1];

extern int input_buffer_y_1_length;
extern int input_buffer_y_2_length;
extern int input_buffer_y_3_length;
extern int input_buffer_y_4_length;
extern int input_buffer_y_5_length;

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

int x_to_px(double x)
{
    return ((x - x_min) * (SCREEN_WIDTH_GRAPH - 1)) / (x_max - x_min);
}

int y_to_py(double y)
{
    return (int) ((y_max - y) * SCREEN_HEIGHT_GRAPH / (y_max - y_min));
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

            if (x % (SCREEN_WIDTH_GRAPH - (x_to_px(M_PI) + 1)) == 0) {
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


            if (y == 0 || y % y_to_py(-1) == 0) {
                for (int x = 0; x < SCREEN_WIDTH_GRAPH; x++) {
                    lv_canvas_set_px(grid, x, y, lv_color_hex(0x808080), LV_OPA_MAX);
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

static void plot_blend(lv_obj_t *grid, int x, int y, lv_color_t color, uint8_t opacity)
{
    if (x >= 0 && x < SCREEN_WIDTH_GRAPH && y >= 0 && y < SCREEN_HEIGHT_GRAPH) {
        lv_canvas_set_px(grid, x, y, color, opacity);
    }
}

static void draw_line_aa(lv_obj_t *grid, int x0, int y0, int x1, int y1, lv_color_t color)
{
    // Xiaolin Wu's line algorithm
    int steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        int tmp;
        tmp = x0;
        x0 = y0;
        y0 = tmp;
        tmp = x1;
        x1 = y1;
        y1 = tmp;
    }
    if (x0 > x1) {
        int tmp;
        tmp = x0;
        x0 = x1;
        x1 = tmp;
        tmp = y0;
        y0 = y1;
        y1 = tmp;
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    double gradient = dx == 0 ? 1.0 : (double) dy / dx;

    // First endpoint
    int xend = x0;
    double yend = y0 + gradient * (xend - x0);
    double xgap = 1.0; // Always full pixel coverage for now
    int xpxl1 = xend;
    int ypxl1 = (int) floor(yend);

    if (steep) {
        plot_blend(grid, ypxl1, xpxl1, color, (uint8_t) ((1 - (yend - ypxl1)) * 255));
        plot_blend(grid, ypxl1 + 1, xpxl1, color, (uint8_t) ((yend - ypxl1) * 255));
    } else {
        plot_blend(grid, xpxl1, ypxl1, color, (uint8_t) ((1 - (yend - ypxl1)) * 255));
        plot_blend(grid, xpxl1, ypxl1 + 1, color, (uint8_t) ((yend - ypxl1) * 255));
    }

    double intery = yend + gradient; // First y-intersection

    // Second endpoint
    xend = x1;
    yend = y1 + gradient * (xend - x1);
    int xpxl2 = xend;
    int ypxl2 = (int) floor(yend);

    if (steep) {
        plot_blend(grid, ypxl2, xpxl2, color, (uint8_t) ((1 - (yend - ypxl2)) * 255));
        plot_blend(grid, ypxl2 + 1, xpxl2, color, (uint8_t) ((yend - ypxl2) * 255));
    } else {
        plot_blend(grid, xpxl2, ypxl2, color, (uint8_t) ((1 - (yend - ypxl2)) * 255));
        plot_blend(grid, xpxl2, ypxl2 + 1, color, (uint8_t) ((yend - ypxl2) * 255));
    }

    // Main loop
    if (steep) {
        for (int x = xpxl1 + 1; x < xpxl2; x++) {
            int y = (int) floor(intery);
            plot_blend(grid, y, x, color, (uint8_t) ((1 - (intery - y)) * 255));
            plot_blend(grid, y + 1, x, color, (uint8_t) ((intery - y) * 255));
            intery += gradient;
        }
    } else {
        for (int x = xpxl1 + 1; x < xpxl2; x++) {
            int y = (int) floor(intery);
            plot_blend(grid, x, y, color, (uint8_t) ((1 - (intery - y)) * 255));
            plot_blend(grid, x, y + 1, color, (uint8_t) ((intery - y) * 255));
            intery += gradient;
        }
    }
}

void draw_graph_func_canvas(const char *func, lv_color_t color)
{
    char original_deg_rad = deg_rad;

    int prev_px = -1;
    int prev_py = -1;

    for (int px = 0; px < SCREEN_WIDTH_GRAPH; px++) {
        double x = x_min + (x_max - x_min) * px / (SCREEN_WIDTH_GRAPH - 1);
        deg_rad = 1;
        x_value = x;
        double y = interpret(func);

        if (y > y_max || y < y_min) {
            prev_px = -1;
            continue;
        }

        int py = (int) ((y_max - y) * SCREEN_HEIGHT_GRAPH / (y_max - y_min));

        if (prev_px >= 0) {
            draw_line_aa(grid, prev_px, prev_py, px, py, color);
        }

        prev_px = px;
        prev_py = py;
    }

    deg_rad = original_deg_rad;
}

void draw_graph(void)
{
    // Draw Y1
    if (strcmp(get_text(input_buffer_y_1, input_buffer_y_1_length), "") != 0) draw_graph_func_canvas(get_text(input_buffer_y_1, input_buffer_y_1_length), lv_palette_main(LV_PALETTE_RED));

    // Draw Y2
    if (strcmp(get_text(input_buffer_y_2, input_buffer_y_2_length), "") != 0) draw_graph_func_canvas(get_text(input_buffer_y_2, input_buffer_y_2_length), lv_palette_main(LV_PALETTE_GREEN));

    // Draw Y3
    if (strcmp(get_text(input_buffer_y_3, input_buffer_y_3_length), "") != 0) draw_graph_func_canvas(get_text(input_buffer_y_3, input_buffer_y_3_length), lv_palette_main(LV_PALETTE_BLUE));

    // Draw Y4
    if (strcmp(get_text(input_buffer_y_4, input_buffer_y_4_length), "") != 0) draw_graph_func_canvas(get_text(input_buffer_y_4, input_buffer_y_4_length), lv_palette_main(LV_PALETTE_ORANGE));

    // Draw Y5
    if (strcmp(get_text(input_buffer_y_5, input_buffer_y_5_length), "") != 0) draw_graph_func_canvas(get_text(input_buffer_y_5, input_buffer_y_5_length), lv_palette_main(LV_PALETTE_PURPLE));

    graph_drawn = 1;

    x_value = 0;
}

void display_screen_graph(void)
{
    lv_obj_move_foreground(status_bar);
    lv_obj_move_foreground(screen_graph_container);
    current_screen = SCREEN_GRAPH;
    if (graph_drawn) create_screen_graph();
    draw_graph();
}
