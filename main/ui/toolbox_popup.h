#define TOOLBOX_1_INDEX_MAX 6
#define TOOLBOX_MAX_VISIBLE 6

extern lv_obj_t *toolbox_popup_buttons_container;

extern bool toolbox_open;
extern lv_obj_t *array_toolbox_1[];
extern char toolbox_1_index;

void create_toolbox_popup(void);
void display_toolbox_popup(void);
