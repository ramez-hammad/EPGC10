#include "interpreter.h"

#include <stdlib.h>
#include <stdio.h>

char *expr;
size_t len;

int main(void)
{
    printf("REPL v0.1\n\nss");
    while (true) {
        printf("> ");
        getline(&expr, &len, stdin);
        printf("%0.1f\n", interpret(expr));
    }
}
