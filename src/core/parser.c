#include "lexer.h"
#include "parser.h"

#include <stdlib.h>
#include <stdio.h>

int next_index = 0;

char *expr = "3*3";

int num_tokens;

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

TOKEN next_token(char look_ahead)
{
    TOKEN *arr_tok = tokenize(expr, &num_tokens);
    TOKEN next;

    if (look_ahead == 0) {
        if (next_index < num_tokens) {
            next = arr_tok[next_index];
            next_index++;
        } else {
            return create_token_op(TOKEN_NULL);
        }
    } else {
        if (next_index < num_tokens) {
            return arr_tok[next_index];
        } else {
            return create_token_op(TOKEN_NULL);
        }
    }
    return next;
}

// factor -> number
NODE *parse_factor(TOKEN *current_token)
{
    switch (current_token->type) {
        case TOKEN_NUM:
            return create_node_lit(current_token->val);
            break;
    }
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
            *current_token = next_token(0);
        } else if (current_token->type == TOKEN_DIV) {
            *current_token = next_token(0);
            current_term = create_node_op(TOKEN_DIV, current_term, parse_factor(current_token));
            *current_token = next_token(0);
        } else if (current_token->type == TOKEN_MINUS || current_token->type == TOKEN_PLUS || current_token->type == TOKEN_NULL) {
            return current_term;
        } else {
            current_term = parse_factor(current_token);
            *current_token = next_token(0);
        }
    }
    return current_term;
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
        } else {
            current_node = parse_term(&current_token);
        }
    }
    return current_node;
}

int main(void)
{
    NODE *root = parse_expression();
    free(root);
    return 0;
}
