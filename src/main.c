#include <stdio.h>
#include <stdlib.h>

#include "helper/helper.h"
#include "math/math.h"

int main(int argc, char **argv) {
    char rotorOne[26] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char rotorTwo[26] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    char rotorThree[26] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    char reflector[26] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

    int *rotorOneInt = word_to_int_array(rotorOne, 26);
    int *rotorTwoInt = word_to_int_array(rotorTwo, 26);
    int *rotorThreeInt = word_to_int_array(rotorThree, 26);
    int *reflectorInt = word_to_int_array(reflector, 26);

    Vector *rotorOneVector = createVector(26, rotorOneInt);
    Vector *rotorTwoVector = createVector(26, rotorTwoInt);
    Vector *rotorThreeVector = createVector(26, rotorThreeInt);
    Vector *reflectorVector = createVector(26, reflectorInt);
    Vector *rotorOneInverseVector = vectorInverseUnderPermutation(*rotorOneVector);
    Vector *rotorTwoInverseVector = vectorInverseUnderPermutation(*rotorTwoVector);
    Vector *rotorThreeInverseVector = vectorInverseUnderPermutation(*rotorThreeVector);

    int letterA = letter_to_int('F');

    int result = rotorOneVector->data[letterA];
    result = rotorTwoVector->data[result];
    result = rotorThreeVector->data[result];
    result = reflectorVector->data[result];
    result = rotorThreeInverseVector->data[result];
    result = rotorTwoInverseVector->data[result];
    result = rotorOneInverseVector->data[result];

    printf("testing with Message 'A' and Rotor Settings 'AAZ'\n");
    printf("Rotor One: %c\n", int_to_letter(result));

    return 0;
}
