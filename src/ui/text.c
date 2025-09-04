#include <text.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <lvgl.h>
#include <screen_graph_input.h>
#include <input_area.h>
#include <var_popup.h>

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

extern uint32_t input_buffer_main_current_pos;
extern uint32_t input_buffer_y_1_current_pos;
extern uint32_t input_buffer_y_2_current_pos;
extern uint32_t input_buffer_y_3_current_pos;
extern uint32_t input_buffer_y_4_current_pos;
extern uint32_t input_buffer_y_5_current_pos;

lv_obj_t *input_area_current;

uint32_t *get_current_pos(void)
{
    input_area_current = get_input_area();

    if (var_popup_open) {
        if (input_area_current == input_area_var_1) return &input_buffer_var_1_current_pos;
        if (input_area_current == input_area_var_2) return &input_buffer_var_2_current_pos;
    }

    if (current_screen == SCREEN_INPUT) return &input_buffer_main_current_pos;

    if (current_screen == SCREEN_GRAPH_INPUT) {
        if (input_area_current == input_area_y_1) return &input_buffer_y_1_current_pos;
        if (input_area_current == input_area_y_2) return &input_buffer_y_2_current_pos;
        if (input_area_current == input_area_y_3) return &input_buffer_y_3_current_pos;
        if (input_area_current == input_area_y_4) return &input_buffer_y_4_current_pos;
        if (input_area_current == input_area_y_5) return &input_buffer_y_5_current_pos;
    }
}

void append_text(char *buffer[], char *text, int *length)
{
    uint32_t current_pos = *get_current_pos();

    int max_length = MAXLEN_INPUT;

    if (var_popup_open) {
        if (get_input_area() == input_area_var_1) max_length = 1;
    }

    if (*length >= max_length) return;

    if (current_pos == *length) {
        buffer[*length] = strdup(text);
    } else {
        for (uint32_t i = *length; i > current_pos; i--) {
            if (i != max_length) buffer[i] = buffer[i - 1];
        }
        buffer[current_pos] = strdup(text);
    }

    (*length)++;
}

char *get_text(char *buffer[], int length)
{
    char *text = (char *) malloc(sizeof(char) * MAXLEN_INPUT * 3);
    text[0] = '\0';

    for (uint32_t i = 0; i < length; i++) {
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

    *get_current_pos() = 0;
}

void delete_text(char *buffer[], int *length)
{
    if (*length == 0) return;

    uint32_t *current_pos = get_current_pos();

    if (*current_pos == *length) {
        free(buffer[*current_pos - 1]);
        buffer[*current_pos - 1] = NULL;
    } else {
        free(buffer[*current_pos - 1]);
        buffer[*current_pos - 1] = NULL;
        for (uint32_t i = *current_pos - 1; i < *length; i++) {
            buffer[i] = buffer[i + 1];
        }
    }

    (*length)--;
}

char **get_buffer(char io)
{
    input_area_current = get_input_area();

    // If input buffer is requested
    if (io == 0) {
        if (input_area_current == input_area_var_1) return input_buffer_var_1;
        if (input_area_current == input_area_var_2) return input_buffer_var_2;

        if (current_screen == SCREEN_INPUT) return input_buffer_main;

        if (current_screen == SCREEN_GRAPH_INPUT) {
            if (input_area_current == input_area_y_1) return input_buffer_y_1;
            if (input_area_current == input_area_y_2) return input_buffer_y_2;
            if (input_area_current == input_area_y_3) return input_buffer_y_3;
            if (input_area_current == input_area_y_4) return input_buffer_y_4;
            if (input_area_current == input_area_y_5) return input_buffer_y_5;
        }
    }

    // If output buffer is requested
    if (io == 1) {
        if (input_area_current == input_area_var_1) return output_buffer_var_1;
        if (input_area_current == input_area_var_2) return output_buffer_var_2;

        if (current_screen == SCREEN_INPUT) return output_buffer_main;

        if (current_screen == SCREEN_GRAPH_INPUT) {
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
    input_area_current = get_input_area();

    // If input buffer length is requested
    if (io == 0) {
        if (input_area_current == input_area_var_1) return &input_buffer_var_1_length;
        if (input_area_current == input_area_var_2) return &input_buffer_var_2_length;

        if (current_screen == SCREEN_INPUT) return &input_buffer_main_length;

        if (current_screen == SCREEN_GRAPH_INPUT) {
            if (input_area_current == input_area_y_1) return &input_buffer_y_1_length;
            if (input_area_current == input_area_y_2) return &input_buffer_y_2_length;
            if (input_area_current == input_area_y_3) return &input_buffer_y_3_length;
            if (input_area_current == input_area_y_4) return &input_buffer_y_4_length;
            if (input_area_current == input_area_y_5) return &input_buffer_y_5_length;
        }
    }

    // If output buffer length is requested
    if (io == 1) {
        if (input_area_current == input_area_var_1) return &output_buffer_var_1_length;
        if (input_area_current == input_area_var_2) return &output_buffer_var_2_length;

        if (current_screen == SCREEN_INPUT) return &output_buffer_main_length;

        if (current_screen == SCREEN_GRAPH_INPUT) {
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
    if (var_popup_open) return get_focused_input_area_var();
    if (current_screen == SCREEN_INPUT) return input_area;
    if (current_screen == SCREEN_GRAPH_INPUT) return get_focused_input_y();
}
