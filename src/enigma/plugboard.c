#include <stdlib.h>

#include "plugboard.h"

Plugboard *plugboardCreate(Vector *wiring) {
    Plugboard *plugboard = malloc(sizeof(Plugboard));
    plugboard->wiring = wiring;
    plugboard->inverseWiring = vectorInverseUnderPermutation(*wiring);

    return plugboard;
}