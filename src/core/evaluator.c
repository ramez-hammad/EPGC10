#include <math.h>
#include <stdbool.h>

#include "lexer.h"
#include "parser.h"

double to_rad(double deg)
{
    return deg * (M_PI / 180);
}

double to_deg(double rad)
{
    return rad * (180 / M_PI);
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
                return evaluate(root->left);
            case TOKEN_UNARY_MINUS:
                switch (root->left->type) {
                    case TOKEN_UNARY_MINUS:
                        root->left->type = TOKEN_UNARY_PLUS;
                        return evaluate(root->left);
                    case TOKEN_UNARY_PLUS:
                        root->left->type = TOKEN_UNARY_MINUS;
                        return evaluate(root->left);
                    case TOKEN_NUM:
                        return root->left->val * -1;
                    case TOKEN_SIN:
                    case TOKEN_COS:
                    case TOKEN_TAN:
                    case TOKEN_SINH:
                    case TOKEN_COSH:
                    case TOKEN_TANH:
                    case TOKEN_ASIN:
                    case TOKEN_ACOS:
                    case TOKEN_ATAN:
                    case TOKEN_ASINH:
                    case TOKEN_ACOSH:
                    case TOKEN_ATANH:
                    case TOKEN_LN:
                    case TOKEN_LOG:
                    case TOKEN_SQRT:
                    case TOKEN_ABS:
                    case TOKEN_VAR:
                        return -1 * evaluate(root->left);
                }
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
                return to_deg(asin(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ACOS:
                return to_deg(acos(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ATAN:
                return to_deg(atan(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ASINH:
                return to_deg(asinh(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ACOSH:
                return to_deg(acosh(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ATANH:
                return to_deg(atanh(evaluate(parse_expression_str(root->arg))));
            case TOKEN_LN:
                return log(evaluate(parse_expression_str(root->arg)));
            case TOKEN_LOG:
                return log10(evaluate(parse_expression_str(root->arg)));
            case TOKEN_SQRT:
                return sqrt(evaluate(parse_expression_str(root->arg)));
            case TOKEN_ABS:
                return fabs(evaluate(parse_expression_str(root->arg)));
            case TOKEN_VAR:
                switch (root->name) {
                    case 'p':
                        return M_PI;
                }
            case TOKEN_NULL:
                return 0;
        }
    }
}
