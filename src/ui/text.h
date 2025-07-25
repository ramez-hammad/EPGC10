#define MAXLEN_INPUT 150

void append_text(char *buffer[], char *text, int *length);
char* get_text(char* buffer[], int *length);
void reset_input_buffer(char *buffer[], int *length);
void delete_text(char *buffer[], int *length);