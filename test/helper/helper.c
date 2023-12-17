#include <unity.h>

#include "../../src/helper/helper.h"
#include "helper.h"

void test_get_number_from_string(void)
{
    int number = 0;
    TEST_ASSERT_EQUAL_INT(0, get_number_from_string("0", &number));
    TEST_ASSERT_EQUAL_INT(0, number);
    TEST_ASSERT_EQUAL_INT(0, get_number_from_string("1", &number));
    TEST_ASSERT_EQUAL_INT(1, number);
    TEST_ASSERT_EQUAL_INT(0, get_number_from_string("10", &number));
    TEST_ASSERT_EQUAL_INT(10, number);
    TEST_ASSERT_EQUAL_INT(0, get_number_from_string("100", &number));
    TEST_ASSERT_EQUAL_INT(100, number);
    TEST_ASSERT_EQUAL_INT(0, get_number_from_string("-1000", &number));
    TEST_ASSERT_EQUAL_INT(-1000, number);
    TEST_ASSERT_EQUAL_INT(0, get_number_from_string("-0100", &number));
    TEST_ASSERT_EQUAL_INT(-100, number);
}

void test_get_number_from_string_error(void)
{
    int number = 0;
    TEST_ASSERT_EQUAL_INT(1, get_number_from_string("a", &number));
    TEST_ASSERT_EQUAL_INT(1, get_number_from_string("1a", &number));
    TEST_ASSERT_EQUAL_INT(1, get_number_from_string("a1", &number));
    TEST_ASSERT_EQUAL_INT(1, get_number_from_string("a1a", &number));
    TEST_ASSERT_EQUAL_INT(1, get_number_from_string("1a1", &number));
    TEST_ASSERT_EQUAL_INT(1, get_number_from_string("-", &number));
}

void run_helper_tests(void)
{
    RUN_TEST(test_get_number_from_string);
    RUN_TEST(test_get_number_from_string_error);
}