#include <stdio.h>
#include <stdlib.h>

#include "cli/cli.h"
#include "enigma/enigma.h"
#include "enigma/reflector.h"
#include "enigma/rotor.h"
#include "helper/helper.h"
#include "math/math.h"

void printWithSpaceEveryNChars(char *string, int n) {
    int stringLength = strlen(string);

    for (int i = 0; i < stringLength; i++) {
        printf("%c", string[i]);

        if ((i + 1) % n == 0) {
            printf(" ");
        }
    }

    printf("\n");
}

int main(int argc, char **argv) {
    ParsedOptions *parsedOptions = parse_options(argc, argv);

    int *rotorOne = word_to_int_array(parsedOptions->rotors[0], ROTOR_SIZE);
    int *rotorTwo = word_to_int_array(parsedOptions->rotors[1], ROTOR_SIZE);
    int *rotorThree = word_to_int_array(parsedOptions->rotors[2], ROTOR_SIZE);
    int *reflector = word_to_int_array(parsedOptions->reflector, ROTOR_SIZE);
    int *ekw = word_to_int_array(EKW, ROTOR_SIZE);
    int *ringSettings = word_to_int_array(parsedOptions->ring_settings, 3);

    Vector *rotorOneVector = createVector(rotorOne);
    Vector *rotorTwoVector = createVector(rotorTwo);
    Vector *rotorThreeVector = createVector(rotorThree);
    Vector *reflectorVector = createVector(reflector);
    Vector *ekwVector = createVector(ekw);
    Vector *rotorOneInverseVector = vectorInverseUnderPermutation(rotorOneVector);
    Vector *rotorTwoInverseVector = vectorInverseUnderPermutation(rotorTwoVector);
    Vector *rotorThreeInverseVector = vectorInverseUnderPermutation(rotorThreeVector);

    Rotor *rotorOneEnigma = createRotor(rotorOneVector, rotorOneInverseVector, ringSettings[0], letter_to_int(parsedOptions->notches[0]));
    Rotor *rotorTwoEnigma = createRotor(rotorTwoVector, rotorTwoInverseVector, ringSettings[1], letter_to_int(parsedOptions->notches[1]));
    Rotor *rotorThreeEnigma = createRotor(rotorThreeVector, rotorThreeInverseVector, ringSettings[2], letter_to_int(parsedOptions->notches[2]));
    Rotor *ekwEnigma = createRotor(ekwVector, ekwVector, 0, 0);
    Reflector *reflectorEnigma = createReflector(reflectorVector);

    Enigma *enigma = enigmaCreate(rotorOneEnigma, rotorTwoEnigma, rotorThreeEnigma, reflectorEnigma, ekwEnigma);

    char *result = enigmaEncrypt(enigma, parsedOptions->input);

    printWithSpaceEveryNChars(result, 5);

    return 0;
}
