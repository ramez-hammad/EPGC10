#include <math.h>
#include <stdbool.h>

#include <lexer.h>
#include <parser.h>

extern char deg_rad;

double deg_to_rad(double deg)
{
    return deg * (M_PI / 180);
}

double grad_to_rad(double grad)
{
    return grad * (M_PI / 200);
}

double rad_to_deg(double rad)
{
    return rad * (180 / M_PI);
}

double rad_to_grad(double rad)
{
    return rad *  (200 / M_PI);
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
                if (deg_rad == 0) return sin(deg_to_rad(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return sin(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return sin(grad_to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_COS:
                if (deg_rad == 0) return cos(deg_to_rad(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return cos(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return cos(grad_to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_TAN:
                if (deg_rad == 0) return tan(deg_to_rad(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return tan(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return tan(grad_to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_SINH:
                if (deg_rad == 0) return sinh(deg_to_rad(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return sinh(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return sinh(grad_to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_COSH:
                if (deg_rad == 0) return cosh(deg_to_rad(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return cosh(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return cosh(grad_to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_TANH:
                if (deg_rad == 0) return tanh(deg_to_rad(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return tanh(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return tanh(grad_to_rad(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ASIN:
                if (deg_rad == 0) return rad_to_deg(asin(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return asin(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return rad_to_grad(asin(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ACOS:
                if (deg_rad == 0) return rad_to_deg(acos(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return acos(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return rad_to_grad(acos(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ATAN:
                if (deg_rad == 0) return rad_to_deg(atan(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return atan(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return rad_to_grad(atan(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ASINH:
                if (deg_rad == 0) return rad_to_deg(asinh(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return asinh(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return rad_to_grad(asinh(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ACOSH:
                if (deg_rad == 0) return rad_to_deg(acosh(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return acosh(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return rad_to_grad(acosh(evaluate(parse_expression_str(root->arg))));
            case TOKEN_ATANH:
                if (deg_rad == 0) return rad_to_deg(atanh(evaluate(parse_expression_str(root->arg))));
                if (deg_rad == 1) return atanh(evaluate(parse_expression_str(root->arg)));
                if (deg_rad == 2) return rad_to_grad(atanh(evaluate(parse_expression_str(root->arg))));
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
