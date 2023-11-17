#include <stdio.h>

#include "rotor/rotor.h"
#include "ukw/ukw.h"

int main(void) {
    Rotor *rotorOne = create_rotor(ROTOR_I, ROTOR_I_INV);
    Rotor *rotorTwo = create_rotor(ROTOR_II, ROTOR_II_INV);
    Rotor *rotorThree = create_rotor(ROTOR_III, ROTOR_III_INV);
    Rotor *reflector = create_rotor(UKW_B, UKW_B);

    int int_array[3] = {0};

    for (int i = 0; i < 3; i++) {
        rotorOne->position++;


        int character = traverse_rotor(rotorOne, int_array[i]);
        character = traverse_rotor(rotorTwo, character);
        character = traverse_rotor(rotorThree, character);
        character = reflector->wiring[character];
        character = traverse_rotor_inverse(rotorThree, character);
        character = traverse_rotor_inverse(rotorTwo, character);
        character = traverse_rotor_inverse(rotorOne, character);

        char debug = character + 'A';
        printf("%c", debug);
    }

    return 0;
}
