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
    int* num_tokens = (int*)malloc(sizeof(int));

    tokenize("3X^2+23X^3+23+265+sin(234)-sinh(43)+log(2)", num_tokens);
    TEST_ASSERT_EQUAL(19, *num_tokens);
    
    tokenize("33000X^23234342+345^XXXX+243434+2XYZ^3234+ln(232.2)+log(2334)", num_tokens);
    TEST_ASSERT_EQUAL(24, *num_tokens);

    tokenize("acosh(234)+32000*sin(32)+2334sin(23)", num_tokens);
    TEST_ASSERT_EQUAL(8, *num_tokens);

    tokenize("ED", num_tokens);
    TEST_ASSERT_EQUAL(2, *num_tokens);

    tokenize("3.14+2*X-sqrt(25)+sin(-X^2)*cos(3/4)-ln(10^-Y)+abs(X-Y)/(1+log(100))^2-tan(Z)+4.5*(X^2+Y^2-Z^2)+(3*X-2)*(2*Y+1)-7+sqrt(X+Y^2-4*X*Y)", num_tokens);
    TEST_ASSERT_EQUAL(61, *num_tokens);

    tokenize("33", num_tokens);
    TEST_ASSERT_EQUAL(1, *num_tokens);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_num_tokens);

    return(UNITY_END());
}
