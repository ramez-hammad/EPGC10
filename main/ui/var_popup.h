extern bool var_popup_open;

void create_var_popup(void);
void display_var_popup(void);

lv_obj_t *get_focused_input_area_var(void);

extern lv_obj_t *input_area_var_1;
extern lv_obj_t *input_area_var_2;

extern char *input_buffer_var_1[], *output_buffer_var_1[];
extern char *input_buffer_var_2[], *output_buffer_var_2[];

extern int input_buffer_var_1_length, output_buffer_var_1_length;
extern int input_buffer_var_2_length, output_buffer_var_2_length;

extern uint32_t input_buffer_var_1_current_pos, output_buffer_var_1_current_pos;
extern uint32_t input_buffer_var_2_current_pos, output_buffer_var_2_current_pos;

extern char var_popup_index;

extern lv_obj_t *array_var_popup[2];

extern lv_obj_t *var_popup_container;