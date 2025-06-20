typedef enum TOKEN_TYPE {
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_POW,
    TOKEN_NUM,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_EQ
} TOKEN_TYPE;

typedef struct TOKEN {
    TOKEN_TYPE type;
    double val; // Only used for numbers
} TOKEN;

TOKEN** tokenize(char* expr);
