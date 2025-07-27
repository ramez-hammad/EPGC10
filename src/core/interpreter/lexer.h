typedef enum TOKEN_TYPE
{
    TOKEN_PLUS,
    TOKEN_MINUS,
    // Unary operators are only identified in the parser
    TOKEN_UNARY_PLUS,
    TOKEN_UNARY_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_POW,
    TOKEN_NUM,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_EQ,
    TOKEN_SIN,
    TOKEN_COS,
    TOKEN_TAN,
    TOKEN_SINH,
    TOKEN_COSH,
    TOKEN_TANH,
    TOKEN_ASIN,
    TOKEN_ACOS,
    TOKEN_ATAN,
    TOKEN_ASINH,
    TOKEN_ACOSH,
    TOKEN_ATANH,
    TOKEN_LN,
    TOKEN_LOG,
    TOKEN_VAR,
    TOKEN_SQRT,
    TOKEN_ABS,
    TOKEN_NULL
} TOKEN_TYPE;

typedef struct TOKEN
{
    TOKEN_TYPE type;
    char name; // Only used for variables
    double val; // Only used for numbers
    char *arg; // Only used for functions
} TOKEN;

TOKEN *tokenize(const char *expr, int *array_size);

TOKEN create_token_op(TOKEN_TYPE type);
