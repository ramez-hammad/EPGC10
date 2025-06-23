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
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_num_tokens);

    return(UNITY_END());
}
