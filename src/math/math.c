#include "math.h"

#include <stdio.h>
#include <stdlib.h>

Vector *createVector(int size, int *data) {
    Vector *v = malloc(sizeof(Vector));
    v->size = size;
    v->data = data;

    return v;
}

void permute(Vector *vector, Vector permutation) {
    if (vector->size != permutation.size) {
        printf("Error: Vector sizes do not match\n");
        exit(1);
    }

    int *data = malloc(sizeof(int) * vector->size);

    for (int i = 0; i < vector->size; i++) {
        data[i] = vector->data[permutation.data[i]];
    }

    vector->data = data;
}

Vector *vectorInverseUnderPermutation(Vector v) {
    int *data = malloc(sizeof(int) * v.size);

    for (int i = 0; i < v.size; i++) {
        data[v.data[i]] = i;
    }

    return createVector(v.size, data);
}
