typedef struct NODE
{
    TOKEN_TYPE type;
    double val; // Only used for numbers
    char name; // Only used for variables
    struct NODE *left;
    struct NODE *right;
} NODE;

NODE *parse_expression();
