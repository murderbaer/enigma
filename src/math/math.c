#include "math.h"

#include <stdio.h>
#include <stdlib.h>

Vector createVector(int size) {
    Vector v;
    v.size = size;
    v.data = (int *)malloc(size * sizeof(int));
    return v;
}

Vector permute(Vector v, Vector p) {
    if (v.size != p.size) {
        printf("Error: Vector sizes do not match\n");
        exit(1);
    }

    Vector result = createVector(v.size);
    for (int i = 0; i < v.size; i++) {
        result.data[i] = v.data[p.data[i]];
    }

    return result;
}

Vector rotate(Vector v, int n) {
    Vector result = createVector(v.size);
    for (int i = 0; i < v.size; i++) {
        result.data[i] = v.data[(i + n) % v.size];
    }

    return result;
}
