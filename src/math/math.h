#pragma once

typedef struct {
    int *data;
} Vector;

Vector *createVector(int *data);

Vector *vectorInverseUnderPermutation(Vector *v);

void vectorRotate(Vector *v, int n);
