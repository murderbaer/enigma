#pragma once

#include "../math/math.h"
#include "rotor.h"

#define NO_NOTCH -1

typedef struct {
    int size;
    Vector *wiring;
    Vector *inverseWiring;
    int notch_1;
    int notch_2;
    int position;
    int ringSetting;
    int turnover;
} Rotor;

int nothing(void);

// Rotor createRotor(int size, Vector *wiring, Vector *notch, int turnover);
// Rotor createRotorFromWiring(int size, Vector *wiring, Vector *notch, int turnover);
// Rotor createRotorFromWiringString(int size, char *wiring, char *notch, int turnover);

// Vector permuteRotor(Rotor r, Vector v);