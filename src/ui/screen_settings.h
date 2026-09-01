#define SCREEN_SETTINGS 4
#define SCREEN_ANGLE 5
#define SCREEN_RESULT_FORMAT 6

void angle_section_click_cb(void);
void create_screen_settings(void);
void display_screen_settings(void);

extern lv_obj_t *screen_settings;

extern lv_obj_t *array_settings_section[2];
extern lv_obj_t *array_settings_angle_section[3];
extern lv_obj_t *array_settings_result_format_section[3];

extern char screen_settings_index;
extern char screen_settings_angle_index;
extern char screen_settings_result_format_index;
