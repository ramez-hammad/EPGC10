#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Create a numerical token with value val
TOKEN* create_token_num(double val)
{
    TOKEN* token = (TOKEN*)malloc(sizeof(TOKEN));
    token->type = TOKEN_NUM;
    token->val = val;
    return token;
}

// Create a token of an operator
TOKEN* create_token_op(TOKEN_TYPE type)
{
    TOKEN* token = (TOKEN*)malloc(sizeof(TOKEN));
    token->type = type;
    return token;
}

char is_num(char c)
{
    if (c >= 48 && c <= 57) // ASCII for 0 and 9
    {
        return 1;
    } else {
        return 0;
    }
}

// Tokenizes the expression and returns a pointer to the array of tokens
TOKEN** tokenize(char* expr)
{
    // Create the initial array of tokens 
    TOKEN** arr_tok = (TOKEN**)malloc(strlen(expr) * sizeof(TOKEN));
    
    // Placeholder number string
    char num[strlen(expr)];
    
    // Number width
    int num_width = 0;

    int num_tokens = 0;
    
    size_t x = 0;
    while (x < strlen(expr))
    {
        if (is_num(expr[x]) == 1)
        {
            num[0] = expr[x];
            for (size_t y = x + 1; y < strlen(expr); y++)
            {
                if (is_num(expr[y]) == 1)
                {
                    num_width++;
                    num[num_width] = expr[y];
                } else {
                    num_width = 0;
                    x = y - 1;
                    break;
                }
            }
            num_tokens++;
            arr_tok[num_tokens-1] = create_token_num(atof(num));
            for (size_t z = 0; z < strlen(expr); z++)
            {
                num[z] = ' ';
            }
        } else {
            switch (expr[x])
            {
                case '+':
                    num_tokens++;
                    arr_tok[num_tokens-1] = create_token_op(TOKEN_PLUS);
                    break;
                case '-':
                    num_tokens++;
                    arr_tok[num_tokens-1] = create_token_op(TOKEN_MINUS);
                    break;
                case '/':
                    num_tokens++;
                    arr_tok[num_tokens-1] = create_token_op(TOKEN_DIV);
                    break;
                case '*':
                    num_tokens++;
                    arr_tok[num_tokens-1] = create_token_op(TOKEN_MUL);
                    break;
                case '(':
                    num_tokens++;
                    arr_tok[num_tokens-1] = create_token_op(TOKEN_LEFT_PAREN);
                    break;
                case ')':
                    num_tokens++;
                    arr_tok[num_tokens-1] = create_token_op(TOKEN_RIGHT_PAREN);
                    break;
                case '^':
                    num_tokens++;
                    arr_tok[num_tokens-1] = create_token_op(TOKEN_POW);
                    break;
                case '=':
                    num_tokens++;
                    arr_tok[num_tokens-1] = create_token_op(TOKEN_EQ);
                    break;
            }
        }
        x++;
    }
    arr_tok = (TOKEN**)realloc(arr_tok, num_tokens * sizeof(TOKEN));
    return arr_tok;
}
