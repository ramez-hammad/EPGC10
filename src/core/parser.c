#include "lexer.h"

#include <stdlib.h>
#include <stdio.h>

int next_index = 0;

char* expr = "3+3*3";

int num_tokens;
TOKEN* arr_tok = tokenize(expr, &num_tokens); 

TOKEN next_token(void)
{
    TOKEN next;
    
    if (next_index < num_tokens)
    {
        next = arr_tok[next_index];
        next_index++;
    } else {
        return NULL;
    }

    return next;
}

/*
 *
 * Creates an abstract syntax tree based on tokens from the lexer, and returns the root node 
 *
 */

NODE parse(void)
{
    TOKEN current_token;

    while (next_index < num_tokens)
    {
        current_token = next_token();
    }
}
