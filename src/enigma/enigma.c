#include <stdlib.h>
#include <string.h>

#include "../helper/helper.h"
#include "enigma.h"
#include "rotor.h"

Enigma *enigmaCreate(Rotor *rotorOne, Rotor *rotorTwo, Rotor *rotorThree, Reflector *reflector, Rotor *ekw) {
    Enigma *enigma = malloc(sizeof(Enigma));
    enigma->rotorOne = rotorOne;
    enigma->rotorTwo = rotorTwo;
    enigma->rotorThree = rotorThree;
    enigma->reflector = reflector;
    enigma->ekw = ekw;

    return enigma;
}

char *enigmaEncrypt(Enigma *enigma, char *message) {
    Rotor *rotorRight = enigma->rotorOne;
    Rotor *rotorMid = enigma->rotorTwo;
    Rotor *rotorLeft = enigma->rotorThree;
    Rotor *ekw = enigma->ekw;
    Reflector *reflector = enigma->reflector;

    int messageLength = strlen(message);
    int newMessageLength = messageLength + messageLength / 4;

    int intMessage[newMessageLength];

    for (size_t i = 0; i < messageLength; i++) {
        int letter = letter_to_int(message[i]);
        char letterChar = int_to_letter(letter);

        // if (enigma->plugboard != NULL) {
        //     letter = plugboardEncrypt(enigma->plugboard, letter);
        // }

        if (rotorRight->position == rotorRight->notch_1) {
            turnRotor(rotorMid);

            if (rotorMid->position == rotorMid->notch_1) {
                turnRotor(rotorLeft);
            }
        }

        turnRotor(rotorRight);

        letter = rotorRight->wiring->data[letter];
        letterChar = int_to_letter(letter);

        letter = rotorMid->wiring->data[(letter - rotorRight->position) % ROTOR_SIZE];
        letterChar = int_to_letter(letter);

        letter = rotorLeft->wiring->data[(letter - rotorMid->position) % ROTOR_SIZE];
        letterChar = int_to_letter(letter);

        letter = reflector->wiring->data[letter];
        letterChar = int_to_letter(letter);

        letter = rotorLeft->inverseWiring->data[letter];
        letterChar = int_to_letter(letter);

        letter = rotorMid->inverseWiring->data[letter];
        letterChar = int_to_letter(letter);

        letter = rotorRight->inverseWiring->data[letter];
        letterChar = int_to_letter(letter);

        // if (enigma->plugboard != NULL) {
        //     letter = plugboardEncrypt(enigma->plugboard, letter);
        // }

        intMessage[i] = ekw->wiring->data[(letter - rotorRight->position) % ROTOR_SIZE];
        letterChar = int_to_letter(intMessage[i]);
    }

    char *result = int_array_to_word(intMessage, strlen(message));

    return result;
}
