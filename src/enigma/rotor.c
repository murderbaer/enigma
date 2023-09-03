#include <stdlib.h>

#include "../helper/helper.h"
#include "../math/math.h"
#include "rotor.h"

Rotor *createRotor(Vector *wiring, Vector *inverseWiring, int ringSetting, int notch) {
    Rotor *rotor = malloc(sizeof(Rotor));

    rotor->wiring = wiring;
    rotor->inverseWiring = inverseWiring;
    rotor->ringSetting = ringSetting;
    rotor->position = 0;
    rotor->notch_1 = notch;

    // for (int i = 0; i < rotor->ringSetting; i++) {
    //     vectorRotate(rotor->wiring, 1);
    //     vectorRotate(rotor->inverseWiring, 1);
    // }

    return rotor;
}

void turnRotor(Rotor *rotor) {
    rotor->position = (rotor->position + 1) % ROTOR_SIZE;
    vectorRotate(rotor->wiring, 1);
    vectorRotate(rotor->inverseWiring, 1);
}
