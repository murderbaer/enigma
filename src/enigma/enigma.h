#pragma once

#include "reflector.h"
#include "rotor.h"

typedef struct {
    Rotor *rotorOne;
    Rotor *rotorTwo;
    Rotor *rotorThree;
    Reflector *reflector;
} Enigma;

Enigma *enigmaCreate(Rotor *rotorOne, Rotor *rotorTwo, Rotor *rotorThree, Reflector *reflector);
char *enigmaEncrypt(Enigma *enigma, char *message);
