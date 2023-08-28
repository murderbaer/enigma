#include <stdio.h>
#include <stdlib.h>

#include "../../src/math/math.h"
#include "../unity/unity.h"

void setUp() {}

void tearDown() {}

void permutateVectorIdentityTest() {
    int size = 5;
    int vData[] = {0, 1, 2, 3, 4};

    Vector *v = createVector(size, vData);
    Vector p;

    int pData[] = {0, 1, 2, 3, 4};
    p.size = size;

    p.data = malloc(sizeof(int) * size);
    p.data = pData;

    permute(v, p);

    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_INT(i, v->data[i]);
    }
}

void permutateVecorInverseTest() {
    int size = 5;
    int vData[] = {0, 1, 2, 3, 4};

    Vector *v = createVector(size, vData);
    Vector p;
    p.size = size;
    p.data = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        p.data[i] = size - i - 1;
    }

    permute(v, p);

    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_INT(size - i - 1, v->data[i]);
    }
}

void permutateCyclicVectorTest() {
    int size = 5;
    int cycles = 3;

    int vData[] = {0, 1, 2, 3, 4};
    Vector *v = createVector(size, vData);
    Vector p;
    p.size = size;

    p.data = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        v->data[i] = i;
        p.data[i] = (i + cycles) % size;
    }

    permute(v, p);

    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_INT((i + cycles) % size, v->data[i]);
    }
}

void permuteVectorInverseTest() {
    int size = 5;

    int vData[] = {0, 1, 2, 3, 4};
    Vector *v = createVector(size, vData);

    Vector *inverse = vectorInverseUnderPermutation(*v);

    for (int i = 0; i < size; i++) {
        TEST_ASSERT_EQUAL_INT(i, inverse->data[v->data[i]]);
    }
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(permutateVectorIdentityTest);
    RUN_TEST(permutateVecorInverseTest);
    RUN_TEST(permutateCyclicVectorTest);
    RUN_TEST(permuteVectorInverseTest);
    UNITY_END();
}