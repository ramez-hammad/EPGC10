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
double y_min = -2.0;
double y_max = 2.0;

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
    lv_obj_set_style_pad_all(screen_graph_container, LV_PART_MAIN, 0);
}

int x_to_px(double x)
{
    return ((x - x_min) * (SCREEN_WIDTH_GRAPH - 1)) / (x_max - x_min);
}

int y_to_py(double y)
{
    return (int) ((y_max - y) * SCREEN_HEIGHT_GRAPH / (y_max - y_min));
}

void safe_set_px(int px, int py, lv_color_t color, int opa)
{
    if (px < SCREEN_WIDTH_GRAPH && px >= 0 && py < SCREEN_HEIGHT_GRAPH && py >= 0) {
        lv_canvas_set_px(grid, px, py, color, opa);
    }
}

void draw_tick_label(char axis, double val, int x, int y)
{
}

void create_screen_graph_grid(void)
{
    lv_obj_clean(screen_graph_container);

    LV_DRAW_BUF_DEFINE_STATIC(draw_buf, 320, 210, LV_COLOR_FORMAT_ARGB8888);
    LV_DRAW_BUF_INIT_STATIC(draw_buf);

    grid = lv_canvas_create(screen_graph_container);
    lv_canvas_set_draw_buf(grid, &draw_buf);
    lv_obj_align(grid, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_scroll_by(screen_graph_container, -160, -105, LV_ANIM_OFF);

    lv_canvas_fill_bg(grid, lv_color_hex(0xffffff), LV_OPA_COVER);

    // Draw vertical gridlines every 1 unit on x-axis
    for (double x = floor(x_min); x <= ceil(x_max); x += 1.0) {
        int px = x_to_px(x);

        for (int y = 0; y < SCREEN_HEIGHT_GRAPH; y++) {
            if (fmod(x, 2) == 0) {
                safe_set_px(px, y, lv_color_hex(0xcccccc), LV_OPA_MAX);
            } else {
                safe_set_px(px, y, lv_color_hex(0xcccccc), LV_OPA_40);
            }
        }

        if (x == 0) {
            for (int y = 0; y < SCREEN_HEIGHT_GRAPH; y++) {
                safe_set_px(px, y, lv_color_hex(0x000000), LV_OPA_MAX);
            }
        }

        // Draw ticks on x-axis
        int y0 = y_to_py(0);
        for (int dy = -3; dy <= 3; dy++) {
            int y_tick = y0 + dy;
            if (y_tick >= 0 && y_tick < SCREEN_HEIGHT_GRAPH) {
                safe_set_px(px, y_tick, lv_color_hex(0x000000), LV_OPA_MAX);
            }
        }

        //draw_tick_label(0, x, px +2, y0 + 4);

        //lv_obj_t *label_x = lv_label_create(screen_graph_container);
        //lv_label_set_text_fmt(label_x, "%.0f", x); // Label text
        //lv_obj_set_style_text_color(label_x, lv_color_hex(0x000000), 0);
        //lv_obj_set_style_text_font(label_x, &lv_font_montserrat_12, 0);

        //// Position label slightly below the x-axis
        //lv_obj_set_pos(label_x, px + 2, y0 + 4);
    }

    int is_y_int = 0;

    // Draw horizontal gridlines every 0.5 units on y-axis
    for (double y = floor(y_min); y <= ceil(y_max); y += 0.5) {
        int py = y_to_py(y);

        is_y_int = is_y_int ^ 1 << 0;

        for (int x = 0; x < SCREEN_WIDTH_GRAPH; x++) {
            if (is_y_int) {
                safe_set_px(x, py, lv_color_hex(0xcccccc), LV_OPA_MAX);
            } else {
                safe_set_px(x, py, lv_color_hex(0xcccccc), LV_OPA_40);
            }
        }

        if (y == 0) {
            for (int x = 0; x < SCREEN_WIDTH_GRAPH; x++) {
                safe_set_px(x, py, lv_color_hex(0x000000), LV_OPA_MAX);
            }
        }

        // Draw ticks on y-axis
        int x0 = x_to_px(0);
        for (int dx = -3; dx <= 3; dx++) {
            int x_tick = x0 + dx;
            if (x_tick >= 0 && x_tick < SCREEN_WIDTH_GRAPH) {
                safe_set_px(x_tick, py, lv_color_hex(0x000000), LV_OPA_MAX);
            }
        }

        //if (y != 0) {
        //lv_obj_t *label_y = lv_label_create(screen_graph_container);
        //lv_label_set_text_fmt(label_y, "%.0f", y); // Label text
        //lv_obj_set_style_text_color(label_y, lv_color_hex(0x000000), 0);
        //lv_obj_set_style_text_font(label_y, &lv_font_montserrat_12, 0);

        //// Position label slightly to the left of the y-axis
        //lv_obj_set_pos(label_y, x0 - 20, py - 5); // Adjust offset as needed
        //}
    }
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

        int py = y_to_py(y);

        if (prev_px != -1) {
            draw_line_aa(grid, prev_px, prev_py, px, py, color);
        }

        prev_px = px;
        prev_py = py;
    }

    deg_rad = original_deg_rad;
}

void create_screen_graph(void)
{
    if (lv_obj_is_valid(screen_graph_container)) lv_obj_delete(screen_graph_container);
    create_screen_graph_container();
    create_screen_graph_grid();
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

    if (graph_drawn) {
        x_min = -2 * M_PI;
        x_max = 2 * M_PI;
        y_min = -2.0;
        y_max = 2.0;

        create_screen_graph();
    }

    draw_graph();
}
