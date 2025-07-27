#include "../lexer.h"
#include "../parser.h"
#include "evaluator.h"

double interpret(const char *expr)
{
    return evaluate(parse_expression_str(expr));
}
