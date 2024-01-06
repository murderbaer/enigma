#include <unity.h>

#include "helper/helper.h"

void setUp(void) {}

void tearDown(void) {}

int main(void)
{
    UNITY_BEGIN();
    run_helper_tests();
    return UNITY_END();
}
