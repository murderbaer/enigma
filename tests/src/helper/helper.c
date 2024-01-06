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

void test_to_upper_case(void)
{
    char output[6] = {0};
    TEST_ASSERT_EQUAL_INT(0, to_upper_case("abcde", output));
    TEST_ASSERT_EQUAL_STRING("ABCDE", output);
    TEST_ASSERT_EQUAL_INT(0, to_upper_case("ABCDE", output));
    TEST_ASSERT_EQUAL_STRING("ABCDE", output);
    TEST_ASSERT_EQUAL_INT(0, to_upper_case("aBcDe", output));
    TEST_ASSERT_EQUAL_STRING("ABCDE", output);
}

void test_to_upper_case_error(void)
{
    char output[6] = {0};
    TEST_ASSERT_EQUAL_INT(1, to_upper_case("12345", output));
    TEST_ASSERT_EQUAL_INT(1, to_upper_case("abcde1", output));
    TEST_ASSERT_EQUAL_INT(1, to_upper_case("1abcde", output));
    TEST_ASSERT_EQUAL_INT(1, to_upper_case("abcde1abcde", output));
    TEST_ASSERT_EQUAL_INT(1, to_upper_case("1abcde1", output));
}

void test_remove_none_alnum(void)
{
    char output[100] = {0};
    TEST_ASSERT_EQUAL_INT(0, remove_none_alnum("abcde", output));
    TEST_ASSERT_EQUAL_STRING("abcde", output);
    TEST_ASSERT_EQUAL_INT(0, remove_none_alnum("a b c d e", output));
    TEST_ASSERT_EQUAL_STRING("abcde", output);
    TEST_ASSERT_EQUAL_INT(0, remove_none_alnum("a  b  c  d  e", output));
    TEST_ASSERT_EQUAL_STRING("abcde", output);
    TEST_ASSERT_EQUAL_INT(0, remove_none_alnum(" a b  c de ", output));
    TEST_ASSERT_EQUAL_STRING("abcde", output);
    TEST_ASSERT_EQUAL_INT(0, remove_none_alnum("a\tb\tc\td\te", output));
    TEST_ASSERT_EQUAL_STRING("abcde", output);
}

void test_remove_none_alnum_error(void) { char output[6] = {0}; }

void run_helper_tests(void)
{
    RUN_TEST(test_get_number_from_string);
    RUN_TEST(test_get_number_from_string_error);
    RUN_TEST(test_to_upper_case);
    RUN_TEST(test_to_upper_case_error);
    RUN_TEST(test_remove_none_alnum);
    RUN_TEST(test_remove_none_alnum_error);
}