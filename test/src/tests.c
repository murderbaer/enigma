#include "../unity/unity.h"
#include "exampleTest.h"

void setUp(void) {}

void tearDown(void) {}

int main(void) {
    UNITY_BEGIN();
    runExampleTest();
    return UNITY_END();
}
