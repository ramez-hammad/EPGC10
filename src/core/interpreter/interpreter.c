#include <lexer.h>
#include <parser.h>
#include <evaluator.h>
#include <error.h>

double interpret(const char *expr)
{
    double ans = evaluate(parse_expression_str(expr));

    // Check if parentheses are mismatched
    if (num_paren != 0) {
        error(0);
        num_paren = 0;
    }

    return ans;
}
