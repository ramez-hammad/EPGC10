typedef struct NODE
{
    TOKEN_TYPE type;
    double val; // Only used for numbers
    char name; // Only used for variables
    char *arg; // Only used for functions
    struct NODE *left;
    struct NODE *right;
} NODE;

void init(const char *expr);

NODE *parse_expression(void);

NODE *parse_expression_str(const char *expr);
