#ifndef APP_H
#define APP_H

#include <lvgl.h>

extern lv_obj_t *array_menu_screen[3][3];

extern char current_screen;
extern double prev_ans;
extern char shift;
extern char alpha;

void create_name_label(void);

void app_create_ui(void);
void app_run(void);

#endif
