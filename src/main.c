#include <stdio.h>
#include <stdlib.h>

#include "helper/helper.h"
#include "math/math.h"

int main() {
    char rotorOne[26] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    char rotorTwo[26] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    char rotorThree[26] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    char reflector[26] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
    char rotorOneInverse[26] = "UWYGADFPVZBECKMTHXSLRINQOJ";
    char rotorTwoInverse[26] = "AJPCZWRLFBDKOTYUQGENHXMIVS";
    char rotorThreeInverse[26] = "TAGBPCSDQEUFVNZHYIXJWLRKOM";

    int *rotorOneInt = word_to_int_array(rotorOne, 26);
    int *rotorTwoInt = word_to_int_array(rotorTwo, 26);
    int *rotorThreeInt = word_to_int_array(rotorThree, 26);
    int *reflectorInt = word_to_int_array(reflector, 26);
    int *rotorOneInverseInt = word_to_int_array(rotorOneInverse, 26);
    int *rotorTwoInverseInt = word_to_int_array(rotorTwoInverse, 26);
    int *rotorThreeInverseInt = word_to_int_array(rotorThreeInverse, 26);

    Vector rotorOneVector = createVector(26);
    Vector rotorTwoVector = createVector(26);
    Vector rotorThreeVector = createVector(26);
    Vector reflectorVector = createVector(26);
    Vector rotorOneInverseVector = createVector(26);
    Vector rotorTwoInverseVector = createVector(26);
    Vector rotorThreeInverseVector = createVector(26);

    for (int i = 0; i < 26; i++) {
        rotorOneVector.data[i] = rotorOneInt[i];
        rotorTwoVector.data[i] = rotorTwoInt[i];
        rotorThreeVector.data[i] = rotorThreeInt[i];
        reflectorVector.data[i] = reflectorInt[i];
        rotorOneInverseVector.data[i] = rotorOneInverseInt[i];
        rotorTwoInverseVector.data[i] = rotorTwoInverseInt[i];
        rotorThreeInverseVector.data[i] = rotorThreeInverseInt[i];
    }

    int letterA = letter_to_int('C');

    int result = rotorOneVector.data[letterA];
    result = rotorTwoVector.data[result];
    result = rotorThreeVector.data[result];
    result = reflectorVector.data[result];
    result = rotorThreeInverseVector.data[result];
    result = rotorTwoInverseVector.data[result];
    result = rotorOneInverseVector.data[result];

    printf("testing with Message 'A' and Rotor Settings 'AAZ'\n");
    printf("Rotor One: %c\n", int_to_letter(result));

    return 0;
}