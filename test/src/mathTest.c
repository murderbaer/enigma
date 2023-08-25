#include "../../src/math/math.h"
#include "../unity/unity.h"

void setUp() {}

void tearDown() {}

void permutateVectorIdentityTest() {
    int size = 5;
    Vector v = createVector(size);
    Vector p = createVector(size);

    for (int i = 0; i < size; i++) {
        v.data[i] = i;
        p.data[i] = i;
    }

    Vector result = permute(v, p);

    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_INT(i, result.data[i]);
    }
}

void permutateVecorInverseTest() {
    int size = 5;
    Vector v = createVector(size);
    Vector p = createVector(size);

    for (int i = 0; i < size; i++) {
        v.data[i] = i;
        p.data[i] = size - i - 1;
    }

    Vector result = permute(v, p);

    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_INT(size - i - 1, result.data[i]);
    }
}

void permutateCyclicVectorTest() {
    int size = 5;
    int cycles = 3;

    Vector v = createVector(size);
    Vector p = createVector(size);

    for (int i = 0; i < size; i++) {
        v.data[i] = i;
        p.data[i] = (i + cycles) % size;
    }

    Vector result = permute(v, p);

    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_INT((i + cycles) % size, result.data[i]);
    }
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(permutateVectorIdentityTest);
    RUN_TEST(permutateVecorInverseTest);
    RUN_TEST(permutateCyclicVectorTest);
    UNITY_END();
}