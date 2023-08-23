#include "math/math.h"

#include <stdio.h>

int main() {
    Vector v = createVector(5);
    v.data[0] = 0;
    v.data[1] = 1;
    v.data[2] = 2;
    v.data[3] = 3;
    v.data[4] = 4;

    Vector p = createVector(5);
    p.data[0] = 4;
    p.data[1] = 3;
    p.data[2] = 2;
    p.data[3] = 1;
    p.data[4] = 0;

    Vector result = permute(v, p);

    for (int i = 0; i < result.size; i++) {
        printf("%d ", result.data[i]);
    }

    printf("\n");

    return 0;
}