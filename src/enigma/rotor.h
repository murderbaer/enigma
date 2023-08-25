#pragma once

#include "math/math.h"

struct Rotor {
    int size;
    Vector *wiring;
    Vector *invWiring;
    Vector *notch;
    int position;
    int ringSetting;
    int turnover;
} typedef Rotor;

int nothing(void);

// Rotor createRotor(int size, Vector *wiring, Vector *notch, int turnover);
// Rotor createRotorFromWiring(int size, Vector *wiring, Vector *notch, int turnover);
// Rotor createRotorFromWiringString(int size, char *wiring, char *notch, int turnover);

// Vector permuteRotor(Rotor r, Vector v);