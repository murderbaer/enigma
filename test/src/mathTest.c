#include <stdio.h>
#include <stdlib.h>

#include "../../src/enigma/rotor.h"
#include "../../src/helper/helper.h"
#include "../../src/math/math.h"
#include "../unity/unity.h"

int vectorEquals(Vector *v1, Vector *v2) {
    for (int i = 0; i < ROTOR_SIZE; i++) {
        if (v1->data[i] != v2->data[i]) {
            return 0;
        }
    }

    return 1;
}

void permutateVecorInverseTest() {
    int *rotorData = malloc(sizeof(int) * ROTOR_SIZE);
    rotorData = word_to_int_array(ROTOR_THREE, ROTOR_SIZE);

    Vector *v = createVector(rotorData);
    Vector *vInverse = vectorInverseUnderPermutation(v);

    TEST_ASSERT_TRUE(vectorEquals(v, vInverse) == 0);

    Vector *vInverseInverse = vectorInverseUnderPermutation(vInverse);

    TEST_ASSERT_TRUE(vectorEquals(v, vInverseInverse) == 1);
}

void permutateCyclicVectorTest() {
    int *rotorData = malloc(sizeof(int) * ROTOR_SIZE);
    rotorData = word_to_int_array(ROTOR_THREE, ROTOR_SIZE);

    Vector *v = createVector(rotorData);
    Vector *vCopy = createVector(rotorData);

    vectorRotate(v, 1);

    TEST_ASSERT_TRUE(vectorEquals(v, vCopy) == 0);

    vectorRotate(v, ROTOR_SIZE - 1);

    TEST_ASSERT_TRUE(vectorEquals(v, vCopy) == 1);
}

void runMathTests() {
    RUN_TEST(permutateVecorInverseTest);
    RUN_TEST(permutateCyclicVectorTest);
}
