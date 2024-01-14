#pragma once

#define M3 3
#define M4 4

#include "rotor/rotor.h"
#include "plugboard/plugboard.h"
#include "reflector/reflector.h"

typedef struct {
    Rotor **rotors;
    int type; // 3 for M3, 4 for M4
    Reflector *reflector;
    Plugboard *plugboard;
    char *plaintext;
} Enigma;

typedef struct EnigmaConfiguration
{
    int *rotors;
    int *rotor_positions;
    int *ring_settings;
    int type;
    char reflector;
    char plugboard[26];
    char message[1024];
} EnigmaConfiguration;

Enigma* create_enigma_from_configuration(EnigmaConfiguration *enigma_configuration);
Enigma* createM3Enigma(Rotor *rotor_one, Rotor *rotor_two, Rotor *rotor_three, Reflector *reflector, Plugboard *plugboard);
Enigma* createM4Enigma(Rotor *rotor_one, Rotor *rotor_two, Rotor *rotor_three, Rotor *rotor_four, Reflector *reflector, Plugboard *plugboard);
int* traverse_enigma(Enigma *enigma);
