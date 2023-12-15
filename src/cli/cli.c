#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../enigma/enigma.h"
#include "../enigma/reflector/reflector.h"
#include "../enigma/rotor/rotor.h"
#include "../helper/helper.h"
#include "cli.h"

#define INPUT_BUFFER_SIZE 50

Enigma *query_input()
{
    char input[INPUT_BUFFER_SIZE];
    char secondary_input[INPUT_BUFFER_SIZE];
    char ternary_input[INPUT_BUFFER_SIZE];

    printf("First Rotor (1, 2, 3, 4, 5, 6, 7):   ");
    fgets(input, INPUT_BUFFER_SIZE, stdin);
    printf("First Rotor offset ('A' or 'B' etc): ");
    fgets(secondary_input, INPUT_BUFFER_SIZE, stdin);
    printf("Position ('A' or 'B' etc): ");
    fgets(ternary_input, INPUT_BUFFER_SIZE, stdin);
    Rotor *rotorOne = create_rotor(input[0] - '0', ternary_input[0] - 'A',
                                   secondary_input[0] - 'A');

    printf("Second Rotor (1, 2, 3, 4, 5, 6, 7):  ");
    fgets(input, INPUT_BUFFER_SIZE, stdin);
    printf("First Rotor offset ('A' or 'B' etc): ");
    fgets(secondary_input, INPUT_BUFFER_SIZE, stdin);
    printf("Position ('A' or 'B' etc):           ");
    fgets(ternary_input, INPUT_BUFFER_SIZE, stdin);
    Rotor *rotorTwo = create_rotor(input[0] - '0', ternary_input[0] - 'A',
                                   secondary_input[0] - 'A');

    printf("Third Rotor (1, 2, 3, 4, 5, 6, 7):   ");
    fgets(input, INPUT_BUFFER_SIZE, stdin);
    printf("First Rotor offset ('A' or 'B' etc): ");
    fgets(secondary_input, INPUT_BUFFER_SIZE, stdin);
    printf("Position ('A' or 'B' etc):           ");
    fgets(ternary_input, INPUT_BUFFER_SIZE, stdin);
    Rotor *rotorThree = create_rotor(input[0] - '0', ternary_input[0] - 'A',
                                     secondary_input[0] - 'A');

    printf("Reflector (B, C):                    ");
    fgets(input, INPUT_BUFFER_SIZE, stdin);
    Reflector *reflector = create_reflector_by_type(input[0]);

    printf("Plugboard (e.g. AB CD EF):           ");
    fgets(input, INPUT_BUFFER_SIZE, stdin);
    Plugboard *plugboard = create_plugboard(input);

    Enigma *enigma      = (Enigma *)malloc(sizeof(Enigma));
    enigma->rotor_one   = rotorOne;
    enigma->rotor_two   = rotorTwo;
    enigma->rotor_three = rotorThree;
    enigma->plugboard   = plugboard;
    enigma->reflector   = reflector;

    return enigma;
}
