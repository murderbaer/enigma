#include "helper.h"

#include <stdlib.h>

int *word_to_int_array(char *char_array, int size) {
    int *int_array = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) {
        int_array[i] = char_array[i] - 'A';
    }

    return int_array;
}

char *int_array_to_word(int *int_array, int size) {
    char *char_array = malloc(sizeof(char) * size);

    for (int i = 0; i < size; i++) {
        char_array[i] = int_array[i] + 'A';
    }

    return char_array;
}

int letter_to_int(char letter) { return letter - 'A'; }

char int_to_letter(int integer) { return integer + 'A'; }
