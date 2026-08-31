#include <interpreter.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *expr;
size_t len;
double prev_ans = 0;
char deg_rad = 0;

int main(void)
{
    // Clear the screen
    printf("\033[2J");

    printf("REPL\n\n");

    while (true) {
        printf("> ");
        if (getline(&expr, &len, stdin) == -1) break;
        if (strcmp(expr, "\n") != 0) printf("%f\n", interpret(expr));
    }
}
