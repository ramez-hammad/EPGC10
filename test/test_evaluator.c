#include "../third_party/Unity/src/unity.h"
#include "../src/core/interpreter/interpreter.h"
#include "../src/core/interpreter/error.h"

double prev_ans = 0;
char deg_rad = 0;

void setUp()
{
}

void tearDown()
{
}

void test_divide_by_zero(void)
{
    error_present = 0;
    double ans = interpret("2/0");

    TEST_ASSERT_EQUAL(1, error_present);
    TEST_ASSERT_EQUAL_STRING("Division by zero", error_message);
    // 2/0 must return 0; the fall-through returned pow(2, 0) = 1.
    TEST_ASSERT_FLOAT_WITHIN(0.000001f, 0.0f, (float) ans);

    error_present = 0;
    ans = interpret("6/3");

    TEST_ASSERT_FLOAT_WITHIN(0.000001f, 2.0f, (float) ans);
    TEST_ASSERT_EQUAL(0, error_present);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_divide_by_zero);

    return (UNITY_END());
}
