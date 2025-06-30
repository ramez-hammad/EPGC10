#include "../third_party/Unity/src/unity.h"
#include "../src/core/lexer.h"
#include <stdlib.h>


void setUp()
{
}

void tearDown()
{
}

void test_num_tokens()
{
    int *num_tokens = (int *) malloc(sizeof(int));

    tokenize("3X^2+23X^3+23+265+sin(234)-sinh(43)+log(2)", num_tokens);
    TEST_ASSERT_EQUAL(19, *num_tokens);

    tokenize("33000X^23234342+345^XXXX+243434+2XYZ^3234+ln(232.2)+log(2334)", num_tokens);
    TEST_ASSERT_EQUAL(24, *num_tokens);

    tokenize("23+23233+23+sin(234)+2", num_tokens);
    TEST_ASSERT_EQUAL(9, *num_tokens);

    tokenize("ED", num_tokens);
    TEST_ASSERT_EQUAL(2, *num_tokens);

    tokenize(
        "3.14+2*X-sqrt(25)+sin(-X^2)*cos(3/4)-ln(10^-Y)+abs(X-Y)/(1+log(100))^2-tan(Z)+4.5*(X^2+Y^2-Z^2)+(3*X-2)*(2*Y+1)-7+sqrt(X+Y^2-4*X*Y)",
        num_tokens);
    TEST_ASSERT_EQUAL(61, *num_tokens);

    tokenize("33", num_tokens);
    TEST_ASSERT_EQUAL(1, *num_tokens);

    tokenize("33+334+343", num_tokens);
    TEST_ASSERT_EQUAL(5, *num_tokens);

    tokenize("3XpeY", num_tokens);
    TEST_ASSERT_EQUAL(5, *num_tokens);

    tokenize("3XYZ(23+sin(23238834ER))", num_tokens);
    TEST_ASSERT_EQUAL(9, *num_tokens);

    tokenize("sin(sinh(arcsin(arcsinh(cos(cosh(arccos(arccosh(tan(tanh(arctan(arctanh(23.00X))))))))))))", num_tokens);
    TEST_ASSERT_EQUAL(1, *num_tokens);
}

void test_func_arg(void)
{
    int *num_tokens = (int *) malloc(sizeof(int));
    TOKEN *array;

    array = tokenize("sin((23))", num_tokens);
    TEST_ASSERT_EQUAL_STRING("(23)", array[0].arg);

    array = tokenize("sinh(23)", num_tokens);
    TEST_ASSERT_EQUAL_STRING("23", array[0].arg);

    array = tokenize("cos(23)", num_tokens);
    TEST_ASSERT_EQUAL_STRING("23", array[0].arg);

    array = tokenize("cosh(23)sin(23)", num_tokens);
    TEST_ASSERT_EQUAL_STRING("23", array[0].arg);
    TEST_ASSERT_EQUAL_STRING("23", array[1].arg);

    array = tokenize("arcsin(23)", num_tokens);
    TEST_ASSERT_EQUAL_STRING("23", array[0].arg);

    array = tokenize("tan(233434.9)", num_tokens);
    TEST_ASSERT_EQUAL_STRING("233434.9", array[0].arg);

    array = tokenize("tan(cos(sin(cosh(arccosh(23.0(23))))))", num_tokens);
    TEST_ASSERT_EQUAL_STRING("cos(sin(cosh(arccosh(23.0(23)))))", array[0].arg);

    array = tokenize("arccosh((2X+3)(2X+3)^2)", num_tokens);
    TEST_ASSERT_EQUAL_STRING("(2X+3)(2X+3)^2", array[0].arg);

    array = tokenize("arcsin(23)", num_tokens);
    TEST_ASSERT_EQUAL_STRING("23", array[0].arg);
}

void test_token_type(void)
{
    int *num_tokens = (int *) malloc(sizeof(int));
    TOKEN *array;

    array = tokenize("arccosh(45)", num_tokens);
    TEST_ASSERT_EQUAL(TOKEN_ACOSH, array[0].type);

    array = tokenize("arcsin(23)", num_tokens);
    TEST_ASSERT_EQUAL(TOKEN_ASIN, array[0].type);

    array = tokenize("arccosh(23)", num_tokens);
    TEST_ASSERT_EQUAL(TOKEN_ACOSH, array[0].type);

    array = tokenize("+", num_tokens);
    TEST_ASSERT_EQUAL(TOKEN_PLUS, array[0].type);

    array = tokenize("3++3", num_tokens);
    TEST_ASSERT_EQUAL(TOKEN_NUM, array[0].type);
    TEST_ASSERT_EQUAL(TOKEN_PLUS, array[1].type);
    TEST_ASSERT_EQUAL(TOKEN_PLUS, array[2].type);
    TEST_ASSERT_EQUAL(TOKEN_NUM, array[3].type);

    array = tokenize("(3+3)*(3+(3/2(sin(23))))", num_tokens);
    TEST_ASSERT_EQUAL(TOKEN_SIN, array[14].type);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_num_tokens);
    RUN_TEST(test_func_arg);
    RUN_TEST(test_token_type);

    return (UNITY_END());
}
