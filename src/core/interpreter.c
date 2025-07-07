#include "parser.h"
#include "evaluator.h"

double interpret(char *expr)
{
    return evaluate(parse_expression_str(expr));
}
