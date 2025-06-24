typedef enum TOKEN_TYPE {
    TOKEN_PLUS,
    TOKEN_MINUS,
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
    TOKEN_ABS
} TOKEN_TYPE;

typedef struct TOKEN {
    TOKEN_TYPE type;
    char name; // Only used for variables
    double val; // Only used for numbers
    char* arg;  // Only used for functions
} TOKEN;

TOKEN* tokenize(char* expr, int* array_size);
