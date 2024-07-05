#pragma once

#define M3 3
#define M4 4

#include "plugboard/plugboard.h"
#include "reflector/reflector.h"
#include "rotor/rotor.h"

typedef struct
{
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

Enigma *
create_enigma_from_configuration(EnigmaConfiguration *enigma_configuration);
int *traverse_enigma(Enigma *enigma);
void free_enigma(Enigma *enigma);
