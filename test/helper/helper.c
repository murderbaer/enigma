#include <unity.h>

#include "helper.h"

void testx(void) { TEST_ASSERT_EQUAL(1, 1); }

void run_helper_tests(void) { RUN_TEST(testx); }