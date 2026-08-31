#define SCREEN_GRAPH_INPUT 2

void create_screen_graph_input(void);

void display_screen_graph_input(void);

lv_obj_t *get_focused_input_y(void);

extern lv_obj_t *input_area_y_1;
extern lv_obj_t *input_area_y_2;
extern lv_obj_t *input_area_y_3;
extern lv_obj_t *input_area_y_4;
extern lv_obj_t *input_area_y_5;

extern char *input_buffer_y_1[], *output_buffer_y_1[];
extern char *input_buffer_y_2[], *output_buffer_y_2[];
extern char *input_buffer_y_3[], *output_buffer_y_3[];
extern char *input_buffer_y_4[], *output_buffer_y_4[];
extern char *input_buffer_y_5[], *output_buffer_y_5[];

extern int input_buffer_y_1_length, output_buffer_y_1_length;
extern int input_buffer_y_2_length, output_buffer_y_2_length;
extern int input_buffer_y_3_length, output_buffer_y_3_length;
extern int input_buffer_y_4_length, output_buffer_y_4_length;
extern int input_buffer_y_5_length, output_buffer_y_5_length;

extern uint32_t input_buffer_y_1_current_pos;
extern uint32_t input_buffer_y_2_current_pos;
extern uint32_t input_buffer_y_3_current_pos;
extern uint32_t input_buffer_y_4_current_pos;
extern uint32_t input_buffer_y_5_current_pos;

extern lv_obj_t *array_graph_input_screen[5];
extern int array_graph_input_screen_index;
