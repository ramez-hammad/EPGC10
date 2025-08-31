#include <lexer.h>
#include <parser.h>
#include <stdlib.h>
#include <stdbool.h>
#include <error.h>
#include <string.h>
#include <tgmath.h>
#include <evaluator.h>

int next_index = 0;

int num_tokens;

int num_paren = 0;

TOKEN *arr_tok;

NODE *create_node_lit(double val)
{
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->type = TOKEN_NUM;
    node->val = val;
    return node;
}

NODE *create_node_op(TOKEN_TYPE type, NODE *left, NODE *right)
{
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}

// Unary operators only have one child
NODE *create_node_unary_op(TOKEN_TYPE type, NODE *left)
{
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->type = type;
    node->left = left;
    return node;
}

NODE *create_node_func(TOKEN_TYPE type, char *arg)
{
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->type = type;
    node->arg = arg;
    return node;
}

NODE *create_node_var(char name)
{
    NODE *node = (NODE *) malloc(sizeof(NODE));
    node->type = TOKEN_VAR;
    node->name = name;
    return node;
}

char is_func(TOKEN_TYPE type)
{
    switch (type) {
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
            return 1;
        default: return 0;
    }
}

void init(const char *expr)
{
    num_tokens = 0;
    next_index = 0;
    arr_tok = tokenize(expr, &num_tokens);
}

void insert_token(TOKEN token, int index, int *num_tokens)
{
    arr_tok = (TOKEN *) realloc(arr_tok, ((*num_tokens) + 1) * sizeof(TOKEN));
    for (int i = *num_tokens - 1; i > index - 1; i--) {
        arr_tok[i + 1] = arr_tok[i];
    }
    arr_tok[index] = token;
    (*num_tokens)++;
}

// look_ahead: 0 -> advance normally
// look_ahead: 1 -> look ahead to the next token
// look_ahead: -1 -> look behind to the previous token
TOKEN next_token(char look_ahead)
{
    if (look_ahead == 0) {
        if (next_index < num_tokens) {
            TOKEN next = arr_tok[next_index];
            next_index++;
            return next;
        } else {
            return create_token_op(TOKEN_NULL);
        }
    } else if (look_ahead == 1) {
        if (next_index < num_tokens) {
            return arr_tok[next_index];
        } else {
            return create_token_op(TOKEN_NULL);
        }
    } else {
        // look_ahead == -1
        /*
         * If current index is not the first index, return the token
         * at the previous index, if the current index is the first one,
         * return TOKEN_NULL
         */
        if (next_index != 1) {
            return arr_tok[next_index - 2];
        } else {
            return create_token_op(TOKEN_NULL);
        }
    }
}

// factor -> (+/-) number
//        -> (+/-) (expression)
//        -> (+/-) variable
//        -> (+/-) function

NODE *parse_factor(TOKEN *current_token)
{
    NODE *current_factor = (NODE *) malloc(sizeof(NODE));
    switch (current_token->type) {
        case TOKEN_MINUS:
            *current_token = next_token(0);
            current_factor = create_node_unary_op(TOKEN_UNARY_MINUS, parse_factor(current_token));
            return current_factor;
        case TOKEN_PLUS:
            *current_token = next_token(0);
            current_factor = create_node_unary_op(TOKEN_UNARY_PLUS, parse_factor(current_token));
            return current_factor;
        case TOKEN_NUM:
            if (next_token(1).type == TOKEN_FACTORIAL) {
                double val = 1;

                if (fmod(current_token->val, 1.0) == 0.0) {
                    for (int i = current_token->val; i > 0; i--) {
                        val *= i;
                    }
                } else {
                    error(0);
                }

                current_factor = create_node_lit(val);
                *current_token = next_token(0);
            } else {
                current_factor = create_node_lit(current_token->val);
            }

            if (next_token(1).type == TOKEN_RIGHT_PAREN) goto right_paren;
            if (next_token(1).type == TOKEN_LEFT_PAREN || next_token(1).type == TOKEN_VAR) goto insert_mul;
            if (next_token(1).type == TOKEN_VAR || is_func(next_token(1).type) == 1) goto insert_mul;

            *current_token = next_token(0);
            return current_factor;
        case TOKEN_FACTORIAL:
            error(0);
        case TOKEN_LEFT_PAREN:
            num_paren++;

            if (next_token(1).type == TOKEN_RIGHT_PAREN) {
                // Syntax Error, () is not valid
                error(0);
                insert_token(create_token_num(0), next_index, &num_tokens);
            }

            if (next_token(1).type == TOKEN_NULL && next_token(-1).type == TOKEN_NULL) {
                error(0);
                insert_token(create_token_num(0), next_index, &num_tokens);
                insert_token(create_token_op(TOKEN_RIGHT_PAREN), next_index + 1, &num_tokens);
            }

            current_factor = parse_expression();
            *current_token = next_token(0);
            return current_factor;
        case TOKEN_RIGHT_PAREN:
            if (next_token(-1).type == TOKEN_NULL) {
                // Syntax Error, first token cannot be a )
                error(0);
                insert_token(create_token_num(0), next_index, &num_tokens);
                *current_token = next_token(0);
                current_factor = parse_factor(current_token);
                return current_factor;
            }
            break;
        case TOKEN_VAR:
            current_factor = create_node_var(current_token->name);
            if (next_token(1).type == TOKEN_RIGHT_PAREN) goto right_paren;
            if (next_token(1).type == TOKEN_LEFT_PAREN) goto insert_mul;
            if (next_token(1).type == TOKEN_VAR) goto insert_mul;

            if (next_token(1).type == TOKEN_FACTORIAL) {
                if (fmod(evaluate(current_factor), 1.0) == 0.0) {
                    double val = 1;

                    for (int i = evaluate(current_factor); i > 0; i--) {
                        val *= i;
                    }

                    current_factor = create_node_lit(val);
                    *current_token = next_token(0);
                } else {
                    error(0);
                }
            }

            *current_token = next_token(0);
            return current_factor;

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
            goto func;

        case TOKEN_NULL:
        case TOKEN_MUL:
        case TOKEN_DIV:
        case TOKEN_POW:
            // Syntax error
            error(0);
            insert_token(create_token_num(0), next_index, &num_tokens);
            *current_token = next_token(0);
            current_factor = parse_factor(current_token);
            return current_factor;
    }

func:
    if (strcmp(current_token->arg, "") == 0) error(0);
    current_factor = create_node_func(current_token->type, current_token->arg);
    if (next_token(1).type == TOKEN_RIGHT_PAREN) goto right_paren;
    if (next_token(1).type == TOKEN_LEFT_PAREN || next_token(1).type == TOKEN_VAR) goto insert_mul;
    if (is_func(next_token(1).type) == 1) goto insert_mul;
    *current_token = next_token(0);
    return current_factor;

insert_mul:
    insert_token(create_token_op(TOKEN_MUL), next_index, &num_tokens);
    *current_token = next_token(0);
    return current_factor;

right_paren:
    for (int i = 0; i < num_tokens; i++) {
        if (next_token(1).type == TOKEN_RIGHT_PAREN) {
            num_paren--;
            next_token(0);
        } else {
            break;
        }
    }

    if (next_token(1).type == TOKEN_LEFT_PAREN) {
        insert_token(create_token_op(TOKEN_MUL), next_index, &num_tokens);
    }

    *current_token = create_token_op(TOKEN_NULL);

    return current_factor;
}

NODE *parse_exponent(TOKEN *current_token)
{
    NODE *current_exponent = (NODE *) malloc(sizeof(NODE));

    current_exponent = parse_factor(current_token);

    while (true) {
        switch (current_token->type) {
            case TOKEN_POW:
                insert_token(create_token_op(TOKEN_LEFT_PAREN), next_index, &num_tokens);
                int temp_index = next_index;
                next_token(0);
                for (int i = 0; i < num_tokens; i++) {
                    switch (next_token(1).type) {
                        case TOKEN_RIGHT_PAREN:
                        case TOKEN_LEFT_PAREN:
                        case TOKEN_PLUS:
                        case TOKEN_MINUS:
                        case TOKEN_POW:
                        case TOKEN_MUL:
                        case TOKEN_DIV:
                        case TOKEN_NUM:
                            next_token(0);
                            continue;
                        default:
                            insert_token(create_token_op(TOKEN_RIGHT_PAREN), next_index, &num_tokens);
                            next_index = temp_index;
                            break;
                    }
                    break;
                }
                *current_token = next_token(0);
                current_exponent = create_node_op(TOKEN_POW, current_exponent, parse_factor(current_token));
                break;
            default: goto ret;
        }
    }
ret:
    return current_exponent;
}

// term -> factor *|/ factor
// Handles multiplication and division of factors
NODE *parse_term(TOKEN *current_token)
{
    NODE *current_term = (NODE *) malloc(sizeof(NODE));

    current_term = parse_exponent(current_token);

    while (true) {
        switch (current_token->type) {
            case TOKEN_MUL:
                *current_token = next_token(0);
                current_term = create_node_op(TOKEN_MUL, current_term, parse_exponent(current_token));
                break;
            case TOKEN_DIV:
                *current_token = next_token(0);
                current_term = create_node_op(TOKEN_DIV, current_term, parse_exponent(current_token));
                break;
            default: goto ret;
        }
    }
ret:
    return current_term;
}

// expression -> term +|- term
// Handles addition and subtraction of terms
NODE *parse_expression(void)
{
    NODE *current_node = (NODE *) malloc(sizeof(NODE));

    TOKEN current_token;

    current_token = next_token(0);
    current_node = parse_term(&current_token);

    while (true) {
        switch (current_token.type) {
            case TOKEN_PLUS:
                current_token = next_token(0);
                current_node = create_node_op(TOKEN_PLUS, current_node, parse_term(&current_token));
                break;
            case TOKEN_MINUS:
                current_token = next_token(0);
                current_node = create_node_op(TOKEN_MINUS, current_node, parse_term(&current_token));
                break;
            default: goto ret;
        }
    }

ret:
    if (num_paren != 0) {
        // Syntax error (Mismatched parentheses)
        error(0);
        num_paren = 0;
    }

    return current_node;
}

// expression -> term +|- term
// Handles addition and subtraction of terms
NODE *parse_expression_str(const char *expr)
{
    init(expr);

    NODE *current_node = (NODE *) malloc(sizeof(NODE));

    TOKEN current_token;

    current_token = next_token(0);
    current_node = parse_term(&current_token);

    while (true) {
        switch (current_token.type) {
            case TOKEN_PLUS:
                current_token = next_token(0);
                current_node = create_node_op(TOKEN_PLUS, current_node, parse_term(&current_token));
                break;
            case TOKEN_MINUS:
                current_token = next_token(0);
                current_node = create_node_op(TOKEN_MINUS, current_node, parse_term(&current_token));
                break;
            default: goto ret;
        }
    }

ret:
    if (num_paren != 0) {
        // Syntax error (Mismatched parentheses)
        error(0);
        num_paren = 0;
    }

    return current_node;
}
