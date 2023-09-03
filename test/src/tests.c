#include "../unity/unity.h"
#include "cliTest.h"
#include "helperTest.h"
#include "mathTest.h"

void setUp() {}

void tearDown() {}

int main() {
    UNITY_BEGIN();
    runMathTests();
    runCliTests();
    runHelperTest();
    return UNITY_END();
}
