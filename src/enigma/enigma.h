#pragma once

#include "rotor/rotor.h"
#include "plugboard/plugboard.h"
#include "reflector/reflector.h"

typedef struct {
    Rotor *rotor_one;
    Rotor *rotor_two;
    Rotor *rotor_three;
    Rotor *rotor_four;
    Reflector *reflector;
    Plugboard *plugboard;
} Enigma;
