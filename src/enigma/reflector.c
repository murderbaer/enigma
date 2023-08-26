#include <stdlib.h>

#include "reflector.h"

Reflector *reflectorCreate(Vector *wiring) {
    Reflector *reflector = malloc(sizeof(Reflector));
    reflector->wiring = wiring;

    return reflector;
}
