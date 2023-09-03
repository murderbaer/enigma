#include <stdio.h>
#include <stdlib.h>

#include "cli/cli.h"
#include "enigma/enigma.h"
#include "enigma/reflector.h"
#include "enigma/rotor.h"
#include "helper/helper.h"
#include "math/math.h"

int main(int argc, char **argv) {
    ParsedOptions *parsedOptions = parse_options(argc, argv);

    int *rotorOne = word_to_int_array(parsedOptions->rotor_on_position_one, 26);
    int *rotorTwo = word_to_int_array(parsedOptions->rotor_on_position_two, 26);
    int *rotorThree = word_to_int_array(parsedOptions->rotor_on_position_three, 26);
    int *reflector = word_to_int_array(parsedOptions->reflector, 26);
    int *ringSettings = word_to_int_array(parsedOptions->ring_settings, 3);

    Vector *rotorOneVector = createVector(rotorOne);
    Vector *rotorTwoVector = createVector(rotorTwo);
    Vector *rotorThreeVector = createVector(rotorThree);
    Vector *reflectorVector = createVector(reflector);
    Vector *rotorOneInverseVector = vectorInverseUnderPermutation(rotorOneVector);
    Vector *rotorTwoInverseVector = vectorInverseUnderPermutation(rotorTwoVector);
    Vector *rotorThreeInverseVector = vectorInverseUnderPermutation(rotorThreeVector);

    Rotor *rotorThreeEnigma = createRotor(rotorOneVector, rotorOneInverseVector, ringSettings[0], 17);
    Rotor *rotorTwoEnigma = createRotor(rotorTwoVector, rotorTwoInverseVector, ringSettings[1], 5);
    Rotor *rotorOneEnigma = createRotor(rotorThreeVector, rotorThreeInverseVector, ringSettings[2], 22);
    Reflector *reflectorEnigma = createReflector(reflectorVector);

    Enigma *enigma = enigmaCreate(rotorOneEnigma, rotorTwoEnigma, rotorThreeEnigma, reflectorEnigma);

    char *result = enigmaEncrypt(enigma, "HELLOWORLD");

    printf("Result: %s\n", result);

    return 0;
}
