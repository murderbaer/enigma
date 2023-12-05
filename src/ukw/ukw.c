#include <stdlib.h>
#include <string.h>

#include "ukw.h"

UKW *create_ukw(char *wiring)
{
    UKW *ukw                 = (UKW *)malloc(sizeof(UKW));
    int wiring_in_number[26] = {0};
    ukw->wiring              = malloc(26 * sizeof(int));

    for (int i = 0; i < 26; i++)
    {
        ukw->wiring[i] = wiring[i] - 'A';
    }

    return ukw;
}
