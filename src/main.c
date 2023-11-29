#include <stdio.h>
#include <stdlib.h>

#include "rotor/rotor.h"
#include "ukw/ukw.h"

int main(void) {
    Rotor *rotorOne = create_rotor(ROTOR_I, ROTOR_I_INV, 'Q');
    Rotor *rotorTwo = create_rotor(ROTOR_II, ROTOR_II_INV, 'E');
    Rotor *rotorThree = create_rotor(ROTOR_III, ROTOR_III_INV, 'V');
    Rotor *reflector = create_rotor(UKW_B, UKW_B, 'Z');

    int int_array[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int array_size = sizeof(int_array)/sizeof(int_array[0]);

    char* output = malloc(array_size * sizeof(char));

    for (int i = 0; i < array_size; i++) {
        rotorOne->position = (rotorOne->position + 1) % 26;

        if (rotorOne->position == rotorOne->notch + 1) {
            rotorTwo->position = (rotorTwo->position + 1) % 26;

            if (rotorTwo->position == rotorTwo->notch + 1) {
                rotorThree->position = (rotorThree->position + 1) % 26;
            }
        }


        char debug = int_array[i] + 'A';
        int character = traverse_rotor(rotorOne, int_array[i]);
        debug = character + rotorOne->position + 'A';
        character = traverse_rotor(rotorTwo, character);
        debug = character + rotorTwo->position + 'A';
        character = traverse_rotor(rotorThree, character);
        debug = character + rotorThree->position + 'A';
        character = reflector->wiring[character];
        debug = character + 'A';
        character = traverse_rotor_inverse(rotorThree, character);
        debug = character + rotorThree->position + 'A';
        character = traverse_rotor_inverse(rotorTwo, character);
        debug = character + rotorTwo->position + 'A';
        character = traverse_rotor_inverse(rotorOne, character);
        debug = character + rotorOne->position + 'A';

        output[i] = character + 'A';
    }

    for (int i = 0; i < array_size; i++) {
        if (i % 5 == 0 && i != 0) {
            printf(" ");
        }

        printf("%c", output[i]);

    }

    return 0;
}

