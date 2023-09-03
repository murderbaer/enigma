#include <stdlib.h>
#include <string.h>

#include "../helper/helper.h"
#include "enigma.h"
#include "rotor.h"

Enigma *enigmaCreate(Rotor *rotorOne, Rotor *rotorTwo, Rotor *rotorThree, Reflector *reflector) {
    Enigma *enigma = malloc(sizeof(Enigma));
    enigma->rotorOne = rotorOne;
    enigma->rotorTwo = rotorTwo;
    enigma->rotorThree = rotorThree;
    enigma->reflector = reflector;

    return enigma;
}

char *enigmaEncrypt(Enigma *enigma, char *message) {
    Rotor *rotorOne = enigma->rotorOne;
    Rotor *rotorTwo = enigma->rotorTwo;
    Rotor *rotorThree = enigma->rotorThree;
    Reflector *reflector = enigma->reflector;

    int intMessage[strlen(message)];

    for (size_t i = 0; i < strlen(message); i++) {
        int letter = letter_to_int(message[i]);

        // if (enigma->plugboard != NULL) {
        //     letter = plugboardEncrypt(enigma->plugboard, letter);
        // }

        turnRotor(rotorOne);

        if (rotorOne->position == rotorOne->notch_1) {
            turnRotor(rotorTwo);
        }

        if (rotorTwo->position == rotorTwo->notch_1) {
            turnRotor(rotorThree);
        }

        letter = rotorOne->wiring->data[letter];
        letter = rotorTwo->wiring->data[(letter + ROTOR_SIZE - rotorOne->position) % ROTOR_SIZE];
        letter = rotorThree->wiring->data[(letter + ROTOR_SIZE - rotorTwo->position) % ROTOR_SIZE];

        letter = reflector->wiring->data[(letter + ROTOR_SIZE - rotorThree->position) % ROTOR_SIZE];

        letter = rotorThree->inverseWiring->data[letter];
        letter = rotorTwo->inverseWiring->data[letter];
        letter = rotorOne->inverseWiring->data[letter];

        // if (enigma->plugboard != NULL) {
        //     letter = plugboardEncrypt(enigma->plugboard, letter);
        // }

        intMessage[i] = (letter + ROTOR_SIZE - rotorOne->position) % ROTOR_SIZE;
    }

    char *result = int_array_to_word(intMessage, strlen(message));

    return result;
}
