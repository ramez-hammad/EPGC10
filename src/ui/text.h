#include "src/misc/lv_types.h"
#define MAXLEN_INPUT 150

uint32_t *get_current_pos(void);

void append_text(char *buffer[], char *text, int *length);

char *get_text(char *buffer[], int length);

void reset_buffer(char *buffer[], int *length);

void delete_text(char *buffer[], int *length);

char **get_buffer(char io);

int *get_length(char io);

lv_obj_t *get_input_area(void);
