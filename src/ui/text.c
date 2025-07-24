#include <text.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint32_t num_strings_input = 0;

void append_text(char *input_buffer[], char *text)
{
    input_buffer[num_strings_input] = strdup(text);
    num_strings_input++;
}

char* get_text(char* input_buffer[])
{
    char *text = (char*) malloc(sizeof(char) * MAXLEN_INPUT * 3);
    text[0] = '\0';

    for (uint32_t i = 0; i < num_strings_input; i++) {
        strcat(text, input_buffer[i]);
    }

    return text;
}

void reset_input_buffer(char *input_buffer[])
{
    for (uint32_t i = 0; i < num_strings_input; i++) {
        free(input_buffer[i]);
        input_buffer[i] = NULL;
    }

    num_strings_input = 0;
}

void delete_text(char *input_buffer[])
{
    if (num_strings_input == 0) return;
    free(input_buffer[num_strings_input - 1]);
    input_buffer[num_strings_input - 1] = NULL;
    num_strings_input--;
}
