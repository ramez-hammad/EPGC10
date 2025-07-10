#include "interpreter.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *expr;
size_t len;

int main(void)
{
    // Clear the screen
    printf("\033[2J");

    printf("REPL\n\n");

    while (true) {
        printf("> ");
        getline(&expr, &len, stdin);
        if (strcmp(expr, "\n") != 0) printf("%0.1f\n", interpret(expr));
    }
}
