#define SCREEN_GRAPH 3

#define SCREEN_WIDTH_GRAPH 320
#define SCREEN_HEIGHT_GRAPH 210

extern double x_min;
extern double x_max;
extern double y_min;
extern double y_max;

extern char graph_slow;
extern char graphing_finished;

typedef struct
{
    lv_obj_t *grid;
    int x0;
    int y0;
    int x1;
    int y1;
    lv_color_t color;
} draw_line_aa_data_t;

typedef struct {
    const char *func;
    lv_color_t color;
    int prev_px, prev_py;
    int px;
} graph_state_t;

void create_screen_graph(void);

void draw_graph(void);

void display_screen_graph(void);
