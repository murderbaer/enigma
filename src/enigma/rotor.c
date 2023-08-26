#include <stdlib.h>

#include "../math/math.h"
#include "rotor.h"

Rotor *rotorCreate(Vector *wiring, int notch_1, int notch_2) {
    Rotor *rotor = malloc(sizeof(Rotor));
    rotor->wiring = wiring;
    rotor->inverseWiring = vectorInverseUnderPermutation(*wiring);
    rotor->notch_1 = notch_1;
    rotor->notch_2 = notch_2;

    return rotor;
}
