#pragma once

#include "../math/math.h"

#define ROTOR_SIZE 26

#define ROTOR_ONE "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define ROTOR_TWO "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define ROTOR_THREE "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define ROTOR_FOUR "ESOVPZJAYQUIRHXLNFTGKDCMWB"
#define ROTOR_FIVE "VZBRGITYUPSDNHLXAWMJQOFECK"
#define ROTOR_SIX "JPGVOUMFYQBENHZRDKASXLICTW"
#define ROTOR_SEVEN "NZJHGRCXMYSWBOUFAIVLPEKQDT"
#define ROTOR_EIGHT "FKQHTLXOCBJSPDZRAMEWNIUYGV"

#define REFLECTOR_A "EJMZALYXVBWFCRQUONTSPIKHGD"
#define REFLECTOR_B "YRUHQSLDPXNGOKMIEBFZCWVJAT"
#define REFLECTOR_C "FVPJIAOYEDRZXWGCTKUQSBNMHL"

typedef struct {
    Vector *wiring;
    Vector *inverseWiring;
    int notch_1;
    int position;
    int ringSetting;
} Rotor;

Rotor *createRotor(Vector *wiring, Vector *inverseWiring, int ringSetting, int notch);
void turnRotor(Rotor *rotor);
