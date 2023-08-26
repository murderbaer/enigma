#pragma once

#include "plugboard.h"
#include "reflector.h"
#include "rotor.h"

typedef struct {
    Rotor *rotorOne;
    Rotor *rotorTwo;
    Rotor *rotorThree;
    Rotor *rotorFour;
    Reflector *reflector;
    Plugboard *plugboard;
} Enigma;