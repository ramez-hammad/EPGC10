#include <math.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"

double to_rad(double deg)
{
    return deg * (M_PI / 180);
}

double evaluate(NODE *root)
{
    while (true) {
        switch (root->type) {
            case TOKEN_PLUS:
                return evaluate(root->left) + evaluate(root->right);
            case TOKEN_MINUS:
                return evaluate(root->left) - evaluate(root->right);
            case TOKEN_MUL:
                return evaluate(root->left) * evaluate(root->right);
            case TOKEN_DIV:
                if (evaluate(root->right) != 0) return evaluate(root->left) / evaluate(root->right);
            // Divide by zero error
            case TOKEN_POW:
                return pow(evaluate(root->left), evaluate(root->right));
            case TOKEN_NUM:
                return root->val;
            case TOKEN_UNARY_PLUS:
                return root->left->val;
            case TOKEN_UNARY_MINUS:
                return root->left->val * -1;
            case TOKEN_SIN:
                return sin(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_COS:
                return cos(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_TAN:
                return tan(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_SINH:
                return sinh(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_COSH:
                return cosh(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_TANH:
                return tanh(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ASIN:
                return asin(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ACOS:
                return acos(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ATAN:
                return atan(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ASINH:
                return asinh(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ACOSH:
                return acosh(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ATANH:
                return atanh(to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_LN:
                return log(evaluate(parse_expression_str(root->arg)));
            case TOKEN_LOG:
                return log10(evaluate(parse_expression_str(root->arg)));
            case TOKEN_SQRT:
                return sqrt(evaluate(parse_expression_str(root->arg)));
            case TOKEN_ABS:
                return fabs(evaluate(parse_expression_str(root->arg)));
            case TOKEN_VAR:
            case TOKEN_NULL:
                return 0;
        }
    }
}
