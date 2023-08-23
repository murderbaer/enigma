#include "../../src/math/math.h"
#include "../unity/unity.h"

void setUp() {}

void tearDown() {}

void permutateIdentityTest() {
    Vector v = createVector(5);
    v.data[0] = 0;
    v.data[1] = 1;
    v.data[2] = 2;
    v.data[3] = 3;
    v.data[4] = 4;

    Vector p = createVector(5);
    p.data[0] = 0;
    p.data[1] = 1;
    p.data[2] = 2;
    p.data[3] = 3;
    p.data[4] = 4;

    Vector result = permute(v, p);

    TEST_ASSERT_EQUAL_INT(0, result.data[0]);
    TEST_ASSERT_EQUAL_INT(1, result.data[1]);
    TEST_ASSERT_EQUAL_INT(2, result.data[2]);
    TEST_ASSERT_EQUAL_INT(3, result.data[3]);
    TEST_ASSERT_EQUAL_INT(4, result.data[4]);

    TEST_MESSAGE("permutateIdentityTest passed");
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(permutateIdentityTest);
    UNITY_END();
}