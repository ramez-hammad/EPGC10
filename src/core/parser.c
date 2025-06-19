#include <string.h>
#include <stdio.h>

// Returns 1 if token is an operator
int is_operator(char token)
{
    if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^')
    {
        return 1;
    } else {
        return 0;
    }
}

/*
 *
 * Converts an arithmetic expression that is in infix form into an abstract
 * syntax tree
 *
 */

char* parse(char expr[])
{
    // Number placeholder
    char x[3] = "";
    
    // Number length placeholder
    int num_len = 0;
    
    // Output string
    static char output_str[50] = "";
    
    // Number of operations
    int num_operations = 0;

    for (size_t h = 0; h < strlen(expr); h++)
    {
        if (h == (strlen(expr) - 1))
        {
            strncat(output_str, &expr[h], 1);
            for (int l = 1; l <= num_operations; l++)
            {
                strcat(output_str, ")");
            }
        }

        if (is_operator(expr[h]) != 1 && expr[h] != ' ')
        {
            x[num_len] = expr[h];
            for (size_t j = h + 1; j < strlen(expr); j++)
            {
                if (is_operator(expr[j]) == 1 || expr[j] == ' ')
                {
                    num_len = 0;
                    break;
                } else {
                    num_len++;
                    x[num_len] = expr[j];
                }
            }
        } else {
            switch (expr[h])
            {
                case '+':
                    strcat(output_str, "ADD(");
                    strcat(output_str, x);
                    strcat(output_str, ", ");
                    num_operations++;
                    break;
                case '-':
                    strcat(output_str, "SUB(");
                    strcat(output_str, x);
                    strcat(output_str, ", ");
                    num_operations++;
                    break;
                case '*':
                    strcat(output_str, "MUL(");
                    strcat(output_str, x);
                    strcat(output_str, ", ");
                    num_operations++;
                    break;
                case '/':
                    strcat(output_str, "DIV(");
                    strcat(output_str, x);
                    strcat(output_str, ", ");
                    num_operations++;
                    break;
                case '^':
                    strcat(output_str, "POW(");
                    strcat(output_str, x);
                    strcat(output_str, ", ");
                    num_operations++;
                    break;
            }
        }
    }
    return output_str;
}
