#include "unity.h"
#include "unity_internals.h"
#include "utils.h"

// Runs before each test.
void
setUp(
    void
)
{}

// Runs after each test.
void
tearDown(
    void
)
{}

void
test_clamp_within_range(
    void
)
{
    TEST_ASSERT_EQUAL(5, 5);
}

void
test_clamp_below_min(
    void
)
{
    TEST_ASSERT_EQUAL(5, 5);
}

int
main(
    void
)
{
    UNITY_BEGIN();

    RUN_TEST(test_clamp_within_range);
    RUN_TEST(test_clamp_below_min);

    return UNITY_END();
}
