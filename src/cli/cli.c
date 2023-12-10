#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../enigma/enigma.h"
#include "../enigma/reflector/reflector.h"
#include "../enigma/rotor/rotor.h"
#include "cli.h"

Enigma *query_input()
{
    char input[50];

    printf("First Rotor (1, 2, 3, 4, 5, 6, 7): ");
    fgets(input, 50, stdin);
    Rotor *rotorOne = create_rotor(input[0] - '0');

    printf("Second Rotor (1, 2, 3, 4, 5, 6, 7): ");
    fgets(input, 50, stdin);
    Rotor *rotorTwo = create_rotor(input[0] - '0');

    printf("Third Rotor (1, 2, 3, 4, 5, 6, 7): ");
    fgets(input, 50, stdin);
    Rotor *rotorThree = create_rotor(input[0] - '0');

    printf("Reflector (B, C): ");
    fgets(input, 50, stdin);
    Reflector *reflector = create_reflector_by_type(input[0]);

    printf("Plugboard (e.g. AB CD EF): ");
    fgets(input, 50, stdin);
    Plugboard *plugboard = create_plugboard(input);

    Enigma *enigma      = (Enigma *)malloc(sizeof(Enigma));
    enigma->rotor_one   = rotorOne;
    enigma->rotor_two   = rotorTwo;
    enigma->rotor_three = rotorThree;
    // enigma->plugboard   = plugboard;
    enigma->reflector = reflector;

    return enigma;
}
