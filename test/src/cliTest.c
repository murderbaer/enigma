#include "../../src/cli/cli.h"
#include "../../src/enigma/rotor.h"
#include "../unity/unity.h"

void checkRotorFormattingTest() {
    TEST_ASSERT_EQUAL_INT(1, checkRotorFormatting(ROTOR_ONE));
    TEST_ASSERT_EQUAL_INT(1, checkRotorFormatting(ROTOR_TWO));
    TEST_ASSERT_EQUAL_INT(1, checkRotorFormatting(ROTOR_THREE));
    TEST_ASSERT_EQUAL_INT(1, checkRotorFormatting(ROTOR_FOUR));
    TEST_ASSERT_EQUAL_INT(1, checkRotorFormatting(ROTOR_FIVE));
    TEST_ASSERT_EQUAL_INT(1, checkRotorFormatting(ROTOR_SIX));
    TEST_ASSERT_EQUAL_INT(1, checkRotorFormatting(ROTOR_SEVEN));
    TEST_ASSERT_EQUAL_INT(1, checkRotorFormatting(ROTOR_EIGHT));
}

void runCliTests() {
    RUN_TEST(checkRotorFormattingTest);
}
