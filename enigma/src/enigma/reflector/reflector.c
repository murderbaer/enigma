#include <stdlib.h>

#include "reflector.h"

Reflector *create_reflector(char *wiring)
{
    Reflector *ukw = (Reflector *)malloc(sizeof(Reflector));
    ukw->wiring    = malloc(26 * sizeof(char));

    for (int i = 0; i < 26; i++)
    {
        ukw->wiring[i] = wiring[i] - 'A';
    }

    return ukw;
}

Reflector *create_reflector_by_type(char type)
{
    if ('C' == type)
    {
        return create_reflector(UKW_C);
    }
    else if ('B' == type)
    {
        return create_reflector(UKW_B);
    }
    else
    {
        return create_reflector(UKW_A);
    }
}
