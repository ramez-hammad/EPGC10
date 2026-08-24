#include <lexer.h>
#include <error.h>

#include <stdlib.h>
#include <string.h>

// Create a token for a number
TOKEN create_token_num(double val)
{
    TOKEN token;
    token.type = TOKEN_NUM;
    token.val = val;
    return token;
}

// Create a token for an operator
TOKEN create_token_op(TOKEN_TYPE type)
{
    TOKEN token;
    token.type = type;
    return token;
}

// Create a token for a function
TOKEN create_token_func(TOKEN_TYPE type, char *arg)
{
    TOKEN token;
    token.type = type;
    token.arg = arg;
    return token;
}

// Create a token for a variable
TOKEN create_token_var(char name)
{
    TOKEN token;
    token.type = TOKEN_VAR;
    token.name = name;
    return token;
}

// Get function argument
char *get_arg(const char *expr, size_t index, int *width)
{
    char *arg = (char *) malloc((strlen(expr) + 1) * sizeof(char));
    int arg_width = 0;
    int num_paren = 0;

    for (; index < strlen(expr); index++) {
        if (expr[index] == '(') {
            num_paren++;
            arg[arg_width] = expr[index];
            arg_width++;
        } else if (expr[index] == ')') {
            num_paren--;
            if (num_paren >= 0) {
                arg[arg_width] = expr[index];
                arg_width++;
            } else {
                break;
            }
        } else {
            arg[arg_width] = expr[index];
            arg_width++;
        }
    }

    *width = arg_width;

    arg[arg_width] = '\0';

    return arg;
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
TOKEN *tokenize(const char *expr, int *array_size)
{
    // Create the initial array of tokens
    TOKEN *arr_tok = (TOKEN *) malloc(strlen(expr) * sizeof(TOKEN));

    // Placeholder number string
    char *num = (char *) malloc(sizeof(char) * (strlen(expr) + 1));
    char *function_arg;

    // Number width
    int num_width = 0;

    int num_tokens = 0;

    int *arg_width = (int *) malloc(sizeof(int));

    size_t x = 0;
    while (x < strlen(expr)) {
        if (is_num(expr[x]) == 1) {
            // Decimal point
            int dp_pres = 0;

            num[0] = expr[x];
            for (size_t y = x + 1; y < strlen(expr); y++) {
                if (is_num(expr[y]) == 1) {
                    num_width++;
                    num[num_width] = expr[y];
                } else if (expr[y] == '.') {
                    if (dp_pres == 1) {
                        // Syntax Error
                        error(0);
                    } else {
                        if (is_num(expr[y + 1]) == 0) error(0);
                        num_width++;
                        num[num_width] = expr[y];
                        dp_pres = 1;
                    }
                } else {
                    break;
                }
            }
            num[num_width + 1] = '\0';
            x = x + num_width;
            num_width = 0;
            num_tokens++;
            arr_tok[num_tokens - 1] = create_token_num(atof(num));
            num[0] = '\0';
        } else {
            switch (expr[x]) {
                case '.':
                    if (is_num(expr[x + 1]) != 1) error(0);

                    num[0] = '0';
                    num[1] = expr[x];

                    num_width = 1;

                    for (size_t y = x + 1; y < strlen(expr); y++) {
                        if (is_num(expr[y]) == 1) {
                            num_width++;
                            num[num_width] = expr[y];
                        } else if (expr[y] == '.') {
                            error(0);
                        } else {
                            break;
                        }
                    }
                    x = x + num_width - 1;
                    num[num_width + 1] = '\0';
                    num_width = 0;
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_num(atof(num));
                    num[0] = '\0';
                    break;

                // Operators
                case '+':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_PLUS);
                    break;
                case '-':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_MINUS);
                    break;
                case '/':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_DIV);
                    break;
                case '*':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_MUL);
                    break;
                case '(':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_LEFT_PAREN);
                    break;
                case ')':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_RIGHT_PAREN);
                    break;
                case '^':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_POW);
                    break;
                case '=':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_EQ);
                    break;
                case '!':
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_op(TOKEN_FACTORIAL);
                    break;

                case 'a':
                    if (expr[x + 2] == 's') // Absolute value function
                    {
                        function_arg = get_arg(expr, x + 4, arg_width);
                        x = x + 3 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_ABS, function_arg);
                        break;
                    }
                    switch (expr[x + 3]) {
                        case 'c':
                            if (expr[x + 6] == '(') // Inverse cosine
                            {
                                function_arg = get_arg(expr, x + 7, arg_width);
                                x = x + 6 + *arg_width + 1;
                                num_tokens++;
                                arr_tok[num_tokens - 1] = create_token_func(TOKEN_ACOS, function_arg);
                                break;
                            } else {
                                // Inverse hyperbolic cosine
                                function_arg = get_arg(expr, x + 8, arg_width);
                                x = x + 7 + *arg_width + 1;
                                num_tokens++;
                                arr_tok[num_tokens - 1] = create_token_func(TOKEN_ACOSH, function_arg);
                                break;
                            }
                        case 's':
                            if (expr[x + 6] == '(') // Inverse sine
                            {
                                function_arg = get_arg(expr, x + 7, arg_width);
                                x = x + 6 + *arg_width + 1;
                                num_tokens++;
                                arr_tok[num_tokens - 1] = create_token_func(TOKEN_ASIN, function_arg);
                                break;
                            } else {
                                // Inverse hyperbolic sine
                                function_arg = get_arg(expr, x + 8, arg_width);
                                x = x + 7 + *arg_width + 1;
                                num_tokens++;
                                arr_tok[num_tokens - 1] = create_token_func(TOKEN_ASINH, function_arg);
                                break;
                            }
                        case 't':
                            if (expr[x + 6] == '(') // Inverse tangent
                            {
                                function_arg = get_arg(expr, x + 7, arg_width);
                                x = x + 6 + *arg_width + 1;
                                num_tokens++;
                                arr_tok[num_tokens - 1] = create_token_func(TOKEN_ATAN, function_arg);
                                break;
                            } else {
                                // Inverse hyperbolic tangent
                                function_arg = get_arg(expr, x + 8, arg_width);
                                x = x + 7 + *arg_width + 1;
                                num_tokens++;
                                arr_tok[num_tokens - 1] = create_token_func(TOKEN_ATANH, function_arg);
                                break;
                            }
                    }
                    break;

                case 's':
                    if (expr[x + 3] == '(') // Sine
                    {
                        function_arg = get_arg(expr, x + 4, arg_width);
                        x = x + 3 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_SIN, function_arg);
                        break;
                    } else if (expr[x + 3] == 'h') {
                        // Hyperbolic sine
                        function_arg = get_arg(expr, x + 5, arg_width);
                        x = x + 4 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_SINH, function_arg);
                        break;
                    } else {
                        // Square root
                        function_arg = get_arg(expr, x + 5, arg_width);
                        x = x + 4 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_SQRT, function_arg);
                        break;
                    }
                case 'c':
                    if (expr[x + 3] == '(') // Cosine
                    {
                        function_arg = get_arg(expr, x + 4, arg_width);
                        x = x + 3 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_COS, function_arg);
                        break;
                    } else {
                        // Hyperbolic cosine
                        function_arg = get_arg(expr, x + 5, arg_width);
                        x = x + 4 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_COSH, function_arg);
                        break;
                    }
                case 't':
                    if (expr[x + 3] == '(') // Tangent
                    {
                        function_arg = get_arg(expr, x + 4, arg_width);
                        x = x + 3 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_TAN, function_arg);
                        break;
                    } else {
                        // Hyperbolic tangent
                        function_arg = get_arg(expr, x + 5, arg_width);
                        x = x + 4 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_TANH, function_arg);
                        break;
                    }
                case 'l':
                    if (expr[x + 1] == 'n') // Natural logarithm
                    {
                        function_arg = get_arg(expr, x + 3, arg_width);
                        x = x + 2 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_LN, function_arg);
                        break;
                    } else {
                        // Logarithm with base 10
                        function_arg = get_arg(expr, x + 4, arg_width);
                        x = x + 3 + *arg_width + 1;
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_func(TOKEN_LOG, function_arg);
                        break;
                    }
                case 'p': // Pi
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_var(expr[x]);
                    break;
                case 'e': // Euler's number
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_var(expr[x]);
                    break;
                case 'x': // Variable x
                    num_tokens++;
                    arr_tok[num_tokens - 1] = create_token_var(expr[x]);
                    break;
                case 'A':
                    // Ans
                    if (expr[x + 1] == 'n') {
                        num_tokens++;
                        arr_tok[num_tokens - 1] = create_token_var('n');
                        x = x + 2;
                    } else {
                        break;
                    }
                    break;
            }

            if (expr[x] <= 90 && expr[x] >= 65) // ASCII for A to Z
            {
                num_tokens++;
                arr_tok[num_tokens - 1] = create_token_var(expr[x]);
            }
        }
        x++;
    }
    arr_tok = (TOKEN *) realloc(arr_tok, num_tokens * sizeof(TOKEN));
    *array_size = num_tokens;
    free(arg_width);
    return arr_tok;
}
