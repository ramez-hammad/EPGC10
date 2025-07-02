#include "lexer.h"
#include "parser.h"

#include <stdlib.h>
#include <stdio.h>

int next_index = 0;

char *expr = "((3+4)*(3+4))";

int num_tokens;

int num_paren = 0;

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

// look_ahead: 0 -> advance normally
// look_ahead: 1 -> look ahead to the next token
// look_ahead: -1 -> look behind to the previous token
TOKEN next_token(char look_ahead)
{
    TOKEN *arr_tok = tokenize(expr, &num_tokens);
    TOKEN next;

    if (look_ahead == 0) {
        if (next_index < num_tokens) {
            next = arr_tok[next_index];
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

// factor -> number
//        -> (expression)
NODE *parse_factor(TOKEN *current_token)
{
    NODE *current_factor = (NODE *) malloc(sizeof(NODE));
    switch (current_token->type) {
        case TOKEN_NUM:
            current_factor = create_node_lit(current_token->val);
            if (next_token(1).type == TOKEN_RIGHT_PAREN) goto right_paren;
            *current_token = next_token(0);
            return current_factor;
        case TOKEN_LEFT_PAREN:
            num_paren++;
            if (next_token(1).type == TOKEN_RIGHT_PAREN); // Syntax Error
            current_factor = parse_expression();
            *current_token = next_token(0);
            return current_factor;

        case TOKEN_RIGHT_PAREN:
            if (next_token(-1).type == TOKEN_NULL || next_token(1).type == TOKEN_LEFT_PAREN) {
                /* Syntax Error, first token cannot be a )
                 * And () is not a valid expression
                 */
            }
    }

right_paren:
    for (int i = 0; i < num_tokens; i++) {
        if (next_token(1).type == TOKEN_RIGHT_PAREN) {
            num_paren--;
            next_token(0);
        } else {
            break;
        }
    }
    *current_token = create_token_op(TOKEN_NULL);
    return current_factor;
}

// term -> factor *|/ factor
// Handles multiplication and division of factors
NODE *parse_term(TOKEN *current_token)
{
    NODE *current_term = (NODE *) malloc(sizeof(NODE));

    while (true) {
        if (current_token->type == TOKEN_MUL) {
            *current_token = next_token(0);
            current_term = create_node_op(TOKEN_MUL, current_term, parse_factor(current_token));
        } else if (current_token->type == TOKEN_DIV) {
            *current_token = next_token(0);
            current_term = create_node_op(TOKEN_DIV, current_term, parse_factor(current_token));
        } else if (current_token->type == TOKEN_MINUS || current_token->type == TOKEN_PLUS || current_token->type ==
                   TOKEN_NULL) {
            return current_term;
        } else {
            current_term = parse_factor(current_token);
        }
    }
}

// expression -> term +|- term
// Handles addition and subtraction of terms
NODE *parse_expression()
{
    NODE *current_node = (NODE *) malloc(sizeof(NODE));

    TOKEN current_token;

    current_token = next_token(0);

    while (next_index < num_tokens) {
        if (current_token.type == TOKEN_PLUS) {
            current_token = next_token(0);
            current_node = create_node_op(TOKEN_PLUS, current_node, parse_term(&current_token));
        } else if (current_token.type == TOKEN_MINUS) {
            current_token = next_token(0);
            current_node = create_node_op(TOKEN_MINUS, current_node, parse_term(&current_token));
        } else if (current_token.type == TOKEN_NULL) {
            return current_node;
        } else {
            current_node = parse_term(&current_token);
        }
    }

    if (num_paren != 0) {
        // Syntax error (Mismatched parentheses)
    }

    return current_node;
}

int main(void)
{
    NODE *root = parse_expression();
    //printf("%d", num_paren);
    free(root);
    return 0;
}
