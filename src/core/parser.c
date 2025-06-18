#include <string.h>

#define MUL(x, y) x * y 
#define DIV(x, y) x / y
#define ADD(x, y) x + y
#define SUB(x, y) x - y

// Returns 1 if token is an operator
int is_operator(char token)
{
    if (token == '+' || token == '-' || token == '*' || token == '/')
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

char parse(char expr)
{

}
