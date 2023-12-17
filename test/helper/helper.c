#include <unity.h>

#include "../../src/helper/helper.h"
#include "helper.h"

void test_get_number_from_string(void)
{
    int number = get_number_from_string("1234");
    TEST_ASSERT_EQUAL_INT(1234, number);
}

void run_helper_tests(void) { RUN_TEST(test_get_number_from_string); }