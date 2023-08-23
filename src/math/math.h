#pragma once

typedef struct {
    int rows;
    int cols;
    int *data;
} Matrix;

typedef struct {
    int size;
    int *data;
} Vector;

Vector createVector(int size);

Vector permute(Vector v, Vector p);