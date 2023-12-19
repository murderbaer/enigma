#pragma once

#define M3 0
#define M4 1

#include "rotor/rotor.h"
#include "plugboard/plugboard.h"
#include "reflector/reflector.h"

typedef struct {
    Rotor *rotor_one;
    Rotor *rotor_two;
    Rotor *rotor_three;
    Rotor *rotor_four;
    int type; // 0 for M3, 1 for M4
    Reflector *reflector;
    Plugboard *plugboard;
    char *plaintext;
} Enigma;

Enigma* createM3Enigma(Rotor *rotor_one, Rotor *rotor_two, Rotor *rotor_three, Reflector *reflector, Plugboard *plugboard);
Enigma* createM4Enigma(Rotor *rotor_one, Rotor *rotor_two, Rotor *rotor_three, Rotor *rotor_four, Reflector *reflector, Plugboard *plugboard);
