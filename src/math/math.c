#include <stdio.h>
#include <stdlib.h>

#include "../enigma/rotor.h"
#include "math.h"

Vector *createVector(int *data) {
    Vector *v = malloc(sizeof(Vector));
    v->data = data;

    return v;
}

Vector *vectorInverseUnderPermutation(Vector *v) {
    int *data = malloc(sizeof(int) * ROTOR_SIZE);

    for (int i = 0; i < ROTOR_SIZE; i++) {
        data[v->data[i]] = i;
    }

    return createVector(data);
}

void vectorRotate(Vector *vector, int amount) {
    int *data = malloc(sizeof(int) * ROTOR_SIZE);

    for (int i = 0; i < ROTOR_SIZE; i++) {
        data[i] = vector->data[(i + amount) % ROTOR_SIZE];
    }

    vector->data = data;
}
