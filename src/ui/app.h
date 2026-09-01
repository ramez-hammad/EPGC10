#ifndef APP_H
#define APP_H

#include <lvgl.h>

extern lv_obj_t *array_menu_screen[3][3];

extern lv_obj_t *input_area;
extern lv_obj_t *input_area_container;
extern lv_obj_t *line;
extern lv_obj_t *ans_label;

extern lv_obj_t *screen_menu;
extern lv_obj_t *screen_menu_container;

extern lv_obj_t *back_button_menu;
extern lv_obj_t *back_button_menu_label;

extern lv_obj_t *graph_button_menu;
extern lv_obj_t *graph_button_menu_label;

extern lv_obj_t *settings_button_menu;
extern lv_obj_t *settings_button_menu_label;

extern lv_obj_t *menu_button_4;
extern lv_obj_t *menu_button_5;
extern lv_obj_t *menu_button_6;
extern lv_obj_t *menu_button_7;
extern lv_obj_t *menu_button_8;
extern lv_obj_t *menu_button_9;

extern char current_screen;
extern double prev_ans;
extern char shift;
extern char alpha;

void create_name_label(void);

void app_create_ui(void);
void app_run(void);

#endif
