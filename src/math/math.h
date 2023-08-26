#pragma once

typedef struct {
    int size;
    int *data;
} Vector;

Vector *createVector(int size, int *data);

void permute(Vector *vector, Vector permutation);

Vector *vectorInverseUnderPermutation(Vector v);

Vector rotate(Vector v, int n);
