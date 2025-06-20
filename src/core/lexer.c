#include "lexer.h"
#include <stdlib.h>
#include <string.h>

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

    for (size_t x = 0; x < strlen(expr); x++)
    {
        if (is_num(expr[x]) == 1)
        {
            num[0] = expr[x];
            for (size_t y = x+1; y < strlen(expr); y++)
            {
                if (is_num(expr[y]) == 1)
                {
                    num_width++;
                    num[num_width] = expr[y];
                } else {
                    num_width = 0;
                    break;
                }
            }
            arr_tok[x] = create_token_num(atoi(num));
            num_tokens++;
        } else {
            switch (expr[x])
            {
                case '+':
                    arr_tok[x] = create_token_op(TOKEN_PLUS);
                    num_tokens++;
                    break;
                case '-':
                    arr_tok[x] = create_token_op(TOKEN_MINUS);
                    num_tokens++;
                    break;
                case '/':
                    arr_tok[x] = create_token_op(TOKEN_DIV);
                    num_tokens++;
                    break;
                case '*':
                    arr_tok[x] = create_token_op(TOKEN_MUL);
                    num_tokens++;
                    break;
                case '(':
                    arr_tok[x] = create_token_op(TOKEN_LEFT_PAREN);
                    num_tokens++;
                    break;
                case ')':
                    arr_tok[x] = create_token_op(TOKEN_RIGHT_PAREN);
                    num_tokens++;
                    break;
                case '^':
                    arr_tok[x] = create_token_op(TOKEN_POW);
                    num_tokens++;
                    break;
                case '=':
                    arr_tok[x] = create_token_op(TOKEN_EQ);
                    num_tokens++;
                    break;
            }
        }
    }
    arr_tok = (TOKEN**)realloc(arr_tok, num_tokens * sizeof(TOKEN));
    return arr_tok;
}
