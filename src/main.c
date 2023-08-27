#include <stdio.h>
#include <stdlib.h>

#include "cli/cli.h"
#include "helper/helper.h"
#include "math/math.h"

int main(int argc, char **argv) {
    ParsedOptions *parsedOptions = parse_options(argc, argv);

    int *rotorOne = word_to_int_array(parsedOptions->rotor_on_position_one, 26);
    int *rotorTwo = word_to_int_array(parsedOptions->rotor_on_position_two, 26);
    int *rotorThree = word_to_int_array(parsedOptions->rotor_on_position_three, 26);
    int *reflector = word_to_int_array(parsedOptions->reflector, 26);

    // if (parsedOptions->rotorCount == 4) {
    //     int *rotorFour = word_to_int_array(parsedOptions->rotor_on_position_four, 26);
    //     Vector *rotorFourVector = createVector(26, rotorFour);
    // }

    Vector *rotorOneVector = createVector(26, rotorOne);
    Vector *rotorTwoVector = createVector(26, rotorTwo);
    Vector *rotorThreeVector = createVector(26, rotorThree);
    Vector *reflectorVector = createVector(26, reflector);
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
