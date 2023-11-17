#include <stdlib.h>
#include <string.h>

#include "rotor.h"

Rotor *create_rotor(char *wiring, char *inverse_wiring)
{
    Rotor *rotor = (Rotor *)malloc(sizeof(Rotor));
    int wiring_in_number[26] = {0};

    for (int i = 0; i < (int)strlen(wiring); i++)
    {
        rotor->wiring[i] = wiring[i] - 'A';
        rotor->inverse_wiring[i] = inverse_wiring[i] - 'A';
    }

    rotor->position = 0;

    return rotor;
}

int traverse_rotor(Rotor *rotor, int character)
{
    int index_from_right = character + rotor->position;
    int index_from_left = rotor->wiring[index_from_right]  - rotor->position;

    if (index_from_left < 0)
    {
        index_from_left += 26;
    }

    return index_from_left;
}

int traverse_rotor_inverse(Rotor *rotor, int character)
{
    int index_from_right = character + rotor->position;
    int index_from_left = rotor->inverse_wiring[index_from_right]  - rotor->position;

    if (index_from_left < 0)
    {
        index_from_left += 26;
    }

    return index_from_left;
}
