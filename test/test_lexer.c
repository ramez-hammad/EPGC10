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
    TOKEN* output = tokenize("3X^2+23X^3+23+265+sin(234)-sinh(43)+log(2)", num_tokens);
    TEST_ASSERT_EQUAL(19, *num_tokens);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_num_tokens);

    return(UNITY_END());
}
