#include "lexer.h"
#include <stdlib.h>
#include <string.h>

// Create a token for a number
TOKEN* create_token_num(double val)
{
    TOKEN* token = (TOKEN*)malloc(sizeof(TOKEN));
    token->type = TOKEN_NUM;
    token->val = val;
    return token;
}

// Create a token for an operator
TOKEN* create_token_op(TOKEN_TYPE type)
{
    TOKEN* token = (TOKEN*)malloc(sizeof(TOKEN));
    token->type = type;
    return token;
}

// Create a token for a function
TOKEN* create_token_func(TOKEN_TYPE type, double arg)
{
    TOKEN* token = (TOKEN*)malloc(sizeof(TOKEN));
    token->type = type;
    token->arg = arg;
    return token;
}

// Create a token for a variable
TOKEN* create_token_var(char name)
{
    TOKEN* token = (TOKEN*)malloc(sizeof(TOKEN));
    token->type = TOKEN_VAR;
    token->name = name;
    return token;
}

// Checks if character is a number
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
                // Operators
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

                // Inverse trigonometric functions
                case 'a':
                    switch (expr[x+3])
                    {
                        case 'c':
                            if (expr[x+6] == '(') // Inverse cosine
                            {
                                for (size_t t = x + 7; t < strlen(expr); t++)
                                {
                                    if (expr[t] == ')')
                                    {
                                        x = x + 6 + num_width + 1;
                                        num_width = 0;
                                        break;
                                    } else {
                                        num[num_width] = expr[t];
                                        num_width++;
                                    }
                                }
                                num_tokens++;
                                arr_tok[num_tokens-1] = create_token_func(TOKEN_ACOS, atof(num));
                                for (size_t z = 0; z < strlen(expr); z++)
                                {
                                    num[z] = ' ';
                                }
                                break;
                            } else { // Inverse hyperbolic cosine
                                for (size_t t = x + 8; t < strlen(expr); t++)
                                {
                                    if (expr[t] == ')')
                                    {
                                        x = x + 7 + num_width + 1;
                                        num_width = 0;
                                        break;
                                    } else {
                                        num[num_width] = expr[t];
                                        num_width++;
                                    }
                                }
                                num_tokens++;
                                arr_tok[num_tokens-1] = create_token_func(TOKEN_ACOSH, atof(num));
                                for (size_t z = 0; z < strlen(expr); z++)
                                {
                                    num[z] = ' ';
                                }
                                break;
                            }
                        case 's': 
                            if (expr[x+6] == '(') // Inverse sine
                            {
                                for (size_t t = x + 7; t < strlen(expr); t++)
                                {
                                    if (expr[t] == ')')
                                    {
                                        x = x + 6 + num_width + 1;
                                        num_width = 0;
                                        break;
                                    } else {
                                        num[num_width] = expr[t];
                                        num_width++;
                                    }
                                }
                                num_tokens++;
                                arr_tok[num_tokens-1] = create_token_func(TOKEN_ASIN, atof(num));
                                for (size_t z = 0; z < strlen(expr); z++)
                                {
                                    num[z] = ' ';
                                }
                                break;
                            } else { // Inverse hyperbolic sine
                                for (size_t t = x + 8; t < strlen(expr); t++)
                                {
                                    if (expr[t] == ')')
                                    {
                                        x = x + 7 + num_width + 1;
                                        num_width = 0;
                                        break;
                                    } else {
                                        num[num_width] = expr[t];
                                        num_width++;
                                    }
                                }
                                num_tokens++;
                                arr_tok[num_tokens-1] = create_token_func(TOKEN_ASINH, atof(num));
                                for (size_t z = 0; z < strlen(expr); z++)
                                {
                                    num[z] = ' ';
                                }
                                break;
                            }
                        case 't': 
                            if (expr[x+6] == '(') // Inverse tangent
                            {
                                for (size_t t = x + 7; t < strlen(expr); t++)
                                {
                                    if (expr[t] == ')')
                                    {
                                        x = x + 6 + num_width + 1;
                                        num_width = 0;
                                        break;
                                    } else {
                                        num[num_width] = expr[t];
                                        num_width++;
                                    }
                                }
                                num_tokens++;
                                arr_tok[num_tokens-1] = create_token_func(TOKEN_ATAN, atof(num));
                                for (size_t z = 0; z < strlen(expr); z++)
                                {
                                    num[z] = ' ';
                                }
                                break;
                            } else { // Inverse hyperbolic tangent
                                for (size_t t = x + 8; t < strlen(expr); t++)
                                {
                                    if (expr[t] == ')')
                                    {
                                        x = x + 7 + num_width + 1;
                                        num_width = 0;
                                        break;
                                    } else {
                                        num[num_width] = expr[t];
                                        num_width++;
                                    }
                                }
                                num_tokens++;
                                arr_tok[num_tokens-1] = create_token_func(TOKEN_ATANH, atof(num));
                                for (size_t z = 0; z < strlen(expr); z++)
                                {
                                    num[z] = ' ';
                                }
                                break;
                            }
                    }
                    break;

                // Trigonometric functions
                case 's':
                    if (expr[x+3] == '(') // Sine
                    {
                        for (size_t t = x + 4; t < strlen(expr); t++)
                        {
                            if (expr[t] == ')')
                            {
                                x = x + 3 + num_width + 1;
                                num_width = 0; 
                                break;
                            } else {
                                num[num_width] = expr[t];
                                num_width++;
                            }
                        }
                        num_tokens++;
                        arr_tok[num_tokens-1] = create_token_func(TOKEN_SIN, atof(num));
                        for (size_t z = 0; z < strlen(expr); z++)
                        {
                            num[z] = ' ';
                        }
                        break;
                    } else { // Hyperbolic sine
                        for (size_t t = x + 5; t < strlen(expr); t++)
                        {
                            if (expr[t] == ')')
                            {
                                x = x + 4 + num_width + 1;
                                num_width = 0;
                                break;
                            } else {
                                num[num_width] = expr[t];
                                num_width++;
                            }
                        }
                        num_tokens++;
                        arr_tok[num_tokens-1] = create_token_func(TOKEN_SINH, atof(num)); 
                        for (size_t z = 0; z < strlen(expr); z++)
                        {
                            num[z] = ' ';
                        }
                        break;
                    }
                case 'c':
                    if (expr[x+3] == '(') // Cosine
                    {
                        for (size_t t = x + 4; t < strlen(expr); t++)
                        {
                            if (expr[t] == ')')
                            {
                                x = x + 3 + num_width + 1;
                                num_width = 0;
                                break;
                            } else {
                                num[num_width] = expr[t];
                                num_width++;
                            }
                        }
                        num_tokens++;
                        arr_tok[num_tokens-1] = create_token_func(TOKEN_COS, atof(num));
                        for (size_t z = 0; z < strlen(expr); z++)
                        {
                            num[z] = ' ';
                        }
                        break;
                    } else { // Hyperbolic cosine
                        for (size_t t = x + 5; t < strlen(expr); t++)
                        {
                            if (expr[t] == ')')
                            {
                                x = x + 4 + num_width + 1;
                                num_width = 0;
                                break;
                            } else {
                                num[num_width] = expr[t];
                                num_width++;
                            }
                        }
                        num_tokens++;
                        arr_tok[num_tokens-1] = create_token_func(TOKEN_COSH, atof(num));
                        for (size_t z = 0; z < strlen(expr); z++)
                        {
                            num[z] = ' ';
                        }
                        break;
                    }
                case 't':
                    if (expr[x+3] == '(') // Tangent
                    {
                        for (size_t t = x + 4; t < strlen(expr); t++)
                        {
                            if (expr[t] == ')')
                            {
                                x = x + 3 + num_width + 1;
                                num_width = 0;
                                break; 
                            } else {
                                num[num_width] = expr[t];
                                num_width++;
                            }
                        }
                        num_tokens++;
                        arr_tok[num_tokens-1] = create_token_func(TOKEN_TAN, atof(num));
                        for (size_t z = 0; z < strlen(expr); z++)
                        {
                            num[z] = ' ';
                        }
                        break;
                    } else { // Hyperbolic tangent
                        for (size_t t = x + 5; t < strlen(expr); t++)
                        {
                            if (expr[t] == ')')
                            {
                                x = x + 4 + num_width + 1;
                                num_width = 0;
                                break;
                            } else {
                                num[num_width] = expr[t];
                                num_width++;
                            }
                        }
                        num_tokens++;
                        arr_tok[num_tokens-1] = create_token_func(TOKEN_TANH, atof(num));
                        for (size_t z = 0; z < strlen(expr); z++)
                        {
                            num[z] = ' ';
                        }
                        break;
                    }
                case 'l':
                    if (expr[x+1] == 'n') // Natural logarithm
                    {
                        for (size_t t = x + 3; t < strlen(expr); t++)
                        {
                            if (expr[t] == ')')
                            {
                                x = x + 2 + num_width + 1;
                                num_width = 0;
                                break;
                            } else {
                                num[num_width] = expr[t];
                                num_width++;
                            }
                        }
                        num_tokens++;
                        arr_tok[num_tokens-1] = create_token_func(TOKEN_LN, atof(num));
                        for (size_t z = 0; z < strlen(expr); z++)
                        {
                            num[z] = ' ';
                        }
                        break;
                    } else { // Logarithm with base 10
                        for (size_t t = x + 4; t < strlen(expr); t++)
                        {
                            if (expr[t] == ')')
                            {
                                x = x + 3 + num_width + 1;
                                num_width = 0;
                                break;
                            } else {
                                num[num_width] = expr[t];
                                num_width++;
                            }
                        }
                        num_tokens++;
                        arr_tok[num_tokens-1] = create_token_func(TOKEN_LOG, atof(num));
                        for (size_t z = 0; z < strlen(expr); z++)
                        {
                            num[z] = ' ';
                        }
                        break;
                    }
            }

            if (expr[x] <= 90 && expr[x] >= 65) // ASCII for A to Z
            {
                num_tokens++;
                arr_tok[num_tokens-1] = create_token_var(expr[x]);
            }
        } 
        x++;
    }
    arr_tok = (TOKEN**)realloc(arr_tok, num_tokens * sizeof(TOKEN));
    return arr_tok;
}
