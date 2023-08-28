#include "../unity/unity.h"
#include "cliTest.h"
#include "mathTest.h"

void setUp() {}

void tearDown() {}

int main() {
    UNITY_BEGIN();
    runMathTests();
    runCliTests();
    return UNITY_END();
}
