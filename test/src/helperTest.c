#include "helperTest.h"
#include "../../src/helper/helper.h"
#include "../unity/unity.h"

void testToIntArrayToWordAndBack() {
    char *word = "HELLO";
    int *intArray = word_to_int_array(word, 5);
    char *newWord = int_array_to_word(intArray, 5);

    TEST_ASSERT_EQUAL_STRING(word, newWord);
}

void runHelperTest() {
    RUN_TEST(testToIntArrayToWordAndBack);
}
