#include <text.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lvgl.h>
#include <screen_graph_input.h>

extern char current_screen;

extern char *input_buffer_main[];
extern char *output_buffer_main[];

extern int input_buffer_main_length;
extern int output_buffer_main_length;

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

extern lv_group_t *group_y;

extern lv_obj_t *input_area_y_1;
extern lv_obj_t *input_area_y_2;
extern lv_obj_t *input_area_y_3;
extern lv_obj_t *input_area_y_4;
extern lv_obj_t *input_area_y_5;
extern lv_obj_t *input_area;

lv_obj_t *input_area_current;

void append_text(char *buffer[], char *text, int *length)
{
    buffer[*length] = strdup(text);
    (*length)++;
}

char *get_text(char *buffer[], int *length)
{
    char *text = (char *) malloc(sizeof(char) * MAXLEN_INPUT * 3);
    text[0] = '\0';

    for (uint32_t i = 0; i < *length; i++) {
        strcat(text, buffer[i]);
    }

    return text;
}

void reset_buffer(char *buffer[], int *length)
{
    for (uint32_t i = 0; i < *length; i++) {
        free(buffer[i]);
        buffer[i] = NULL;
    }

    *length = 0;
}

void delete_text(char *buffer[], int *length)
{
    if (*length == 0) return;
    free(buffer[*length - 1]);
    buffer[*length - 1] = NULL;
    (*length)--;
}

char **get_buffer(char io)
{
    input_area_current = get_focused_input_y();

    // If input buffer is requested
    if (io == 0) {
        if (current_screen == 0) return input_buffer_main;

        if (current_screen == 2) {
            if (input_area_current == input_area_y_1) return input_buffer_y_1;
            if (input_area_current == input_area_y_2) return input_buffer_y_2;
            if (input_area_current == input_area_y_3) return input_buffer_y_3;
            if (input_area_current == input_area_y_4) return input_buffer_y_4;
            if (input_area_current == input_area_y_5) return input_buffer_y_5;
        }
    }

    // If  output buffer is requested
    if (io == 1) {
        if (current_screen == 0) return output_buffer_main;

        if (current_screen == 2) {
            if (input_area_current == input_area_y_1) return output_buffer_y_1;
            if (input_area_current == input_area_y_2) return output_buffer_y_2;
            if (input_area_current == input_area_y_3) return output_buffer_y_3;
            if (input_area_current == input_area_y_4) return output_buffer_y_4;
            if (input_area_current == input_area_y_5) return output_buffer_y_5;
        }
    }
}

int *get_length(char io)
{
    input_area_current = get_focused_input_y();

    // If input buffer length is requested
    if (io == 0) {
        if (current_screen == 0) return &input_buffer_main_length;

        if (current_screen == 2) {
            if (input_area_current == input_area_y_1) return &input_buffer_y_1_length;
            if (input_area_current == input_area_y_2) return &input_buffer_y_2_length;
            if (input_area_current == input_area_y_3) return &input_buffer_y_3_length;
            if (input_area_current == input_area_y_4) return &input_buffer_y_4_length;
            if (input_area_current == input_area_y_5) return &input_buffer_y_5_length;
        }
    }

    // If  output buffer length is requested
    if (io == 1) {
        if (current_screen == 0) return &output_buffer_main_length;

        if (current_screen == 2) {
            if (input_area_current == input_area_y_1) return &output_buffer_y_1_length;
            if (input_area_current == input_area_y_2) return &output_buffer_y_2_length;
            if (input_area_current == input_area_y_3) return &output_buffer_y_3_length;
            if (input_area_current == input_area_y_4) return &output_buffer_y_4_length;
            if (input_area_current == input_area_y_5) return &output_buffer_y_5_length;
        }
    }
}

lv_obj_t *get_input_area(void)
{
    if (current_screen == 0) return input_area;
    if (current_screen == 2) return get_focused_input_y();
}
