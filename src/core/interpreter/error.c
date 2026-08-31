#include <string.h>

char error_present = 0;

char error_message[17];

void error(char error)
{
    error_present = 1;

    switch (error) {
        // Syntax error
        case 0:
            strcpy(error_message, "Syntax error");
            break;
        case 1:
            strcpy(error_message, "Division by zero");
            break;
        case 2:
            strcpy(error_message, "Argument error");
            break;
    }
}
