#include <stdio.h>

#include "helper/helper.h"
#include "math/math.h"

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

    // Vector result = permute(v, p);

    char test[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";

    int size = sizeof(test) / sizeof(test[0]) - 1;

    int *test_int = word_to_int_array(test, size);
    char *test_char = int_array_to_word(test_int, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", test_int[i]);
    }

    printf("\n");

    int j = 0;

    for (int i = 0; i < size; i++) {
        j++;
        printf("%c ", test_char[i]);
    }

    printf("\n");

    printf("%d\n", j);

    v = createVector(size);

    for (int i = 0; i < size; i++) {
        v.data[i] = test_int[i];
    }

    p = createVector(size);

    for (int i = 0; i < size; i++) {
        p.data[i] = (i + 1) % size;
    }

    Vector result = permute(v, p);

    for (int i = 0; i < size; i++) {
        printf("%d ", result.data[i]);
    }

    return 0;
}