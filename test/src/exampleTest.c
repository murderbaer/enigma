#include <unity.h>

#include "../../src/example_module/example.h"
#include "exampleTest.h"

void exampleToTest(void) {
    example_function();

    TEST_ASSERT(1);
}

void runExampleTest(void) {
    RUN_TEST(exampleToTest);
}
