#include <string.h>
#include <stdlib.h>

#include "ukw.h"

UKW *create_ukw(char *wiring) {
    UKW *ukw = (UKW *)malloc(sizeof(UKW));
    int wiring_in_number[26] = {0};

    for (int i = 0; i < 26; i++) {
        ukw->wiring[i] = wiring[i] - 'A';
    }

    return ukw;
}
