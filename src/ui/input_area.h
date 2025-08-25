#define SCREEN_INPUT 0

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

extern lv_obj_t *input_base;

void create_input_base(void);

void create_input_area_container(void);

void create_input_area(void);

void create_line_ans(void);

void create_ans_label(double ans);

void display_screen_input(void);

void add_to_input_area(char *text);

void delete_from_input_area(void);

void input_area_nav_left(void);

void input_area_nav_right(void);
