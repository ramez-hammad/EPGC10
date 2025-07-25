#include <text.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void append_text(char *buffer[], char *text, int *length)
{
    buffer[*length] = strdup(text);
    (*length)++;
}

char* get_text(char* buffer[], int *length)
{
    char *text = (char*) malloc(sizeof(char) * MAXLEN_INPUT * 3);
    text[0] = '\0';

    for (uint32_t i = 0; i < *length; i++) {
        strcat(text, buffer[i]);
    }

    return text;
}

void reset_input_buffer(char *buffer[], int *length)
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
