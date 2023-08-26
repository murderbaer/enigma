#include <stdlib.h>

#include "enigma.h"

Enigma *enigmaCreate(Rotor *rotorOne, Rotor *rotorTwo, Rotor *rotorThree, Rotor *rotorFour, Reflector *reflector, Plugboard *plugboard) {
    Enigma *enigma = malloc(sizeof(Enigma));
    enigma->rotorOne = rotorOne;
    enigma->rotorTwo = rotorTwo;
    enigma->rotorThree = rotorThree;
    enigma->rotorFour = rotorFour;
    enigma->reflector = reflector;
    enigma->plugboard = plugboard;

    return enigma;
}
