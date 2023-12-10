#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rotor.h"

int should_rotate(Rotor *rotor)
{
    for (int i = 0; i < rotor->notch_count; i++)
    {
        if (rotor->position == rotor->notch[i] + 1)
        {
            return 1;
        }
    }

    return 0;
}

int *char_to_int_array(char *string)
{
    int *int_array = malloc(strlen(string) * sizeof(int));

    for (int i = 0; i < (int)strlen(string); i++)
    {
        int_array[i] = string[i] - 'A';
    }

    return int_array;
}

Rotor *create_one_notch_rotor(char *wiring, char *inverse_wiring, char notch)
{
    Rotor *rotor             = (Rotor *)malloc(sizeof(Rotor));
    int wiring_in_number[26] = {0};

    for (int i = 0; i < (int)strlen(wiring); i++)
    {
        rotor->wiring[i]         = wiring[i] - 'A';
        rotor->inverse_wiring[i] = inverse_wiring[i] - 'A';
    }

    rotor->position    = 0;
    rotor->notch_count = 1;
    rotor->notch       = malloc(1 * sizeof(int));
    rotor->notch[0]    = notch - 'A';

    return rotor;
}

Rotor *create_two_notch_rotor(char *wiring, char *inverse_wiring, char notch1,
                              char notch2)
{
    Rotor *rotor             = (Rotor *)malloc(sizeof(Rotor));
    int wiring_in_number[26] = {0};

    for (int i = 0; i < (int)strlen(wiring); i++)
    {
        rotor->wiring[i]         = wiring[i] - 'A';
        rotor->inverse_wiring[i] = inverse_wiring[i] - 'A';
    }

    rotor->position    = 0;
    rotor->notch_count = 2;
    rotor->notch       = malloc(2 * sizeof(int));
    rotor->notch[0]    = notch1 - 'A';
    rotor->notch[1]    = notch2 - 'A';

    return rotor;
}

Rotor *create_rotor(int type)
{
    printf("Rotor as int type%d", type);

    switch (type)
    {
    case 1:
        return create_one_notch_rotor(ROTOR_I, ROTOR_I_INV, ROTOR_I_NOTCH);
        break;
    case 2:
        return create_one_notch_rotor(ROTOR_II, ROTOR_II_INV, ROTOR_II_NOTCH);
        break;
    case 3:
        return create_one_notch_rotor(ROTOR_III, ROTOR_III_INV,
                                      ROTOR_III_NOTCH);
        break;
    case 4:
        return create_one_notch_rotor(ROTOR_IV, ROTOR_IV_INV, ROTOR_IV_NOTCH);
        break;
    case 5:
        return create_one_notch_rotor(ROTOR_V, ROTOR_V_INV, ROTOR_V_NOTCH);
        break;
    case 6:
        return create_two_notch_rotor(ROTOR_VI, ROTOR_VI_INV,
                                      ROTOR_VI_NOTCH_ONE, ROTOR_VI_NOTCH_TWO);
        break;
    case 7:
        return create_two_notch_rotor(ROTOR_VII, ROTOR_VII_INV,
                                      ROTOR_VII_NOTCH_ONE, ROTOR_VII_NOTCH_TWO);
        break;
    case 8:
        return create_two_notch_rotor(ROTOR_VIII, ROTOR_VIII_INV,
                                      ROTOR_VIII_NOTCH_ONE,
                                      ROTOR_VIII_NOTCH_TWO);
        break;
    default:
        printf("Error, Rotor defintion not found");
        exit(1);
    }
}

int traverse_rotor(Rotor *rotor, int character)
{
    int index_from_right = (character + rotor->position) % 26;
    int index_from_left  = rotor->wiring[index_from_right] - rotor->position;

    if (index_from_left < 0)
    {
        index_from_left += 26;
    }

    index_from_left = index_from_left % 26;

    return index_from_left;
}

int traverse_rotor_inverse(Rotor *rotor, int character)
{
    int index_from_left = (character + rotor->position) % 26;
    int index_from_right =
        rotor->inverse_wiring[index_from_left] - rotor->position;

    if (index_from_right < 0)
    {
        index_from_right += 26;
    }

    index_from_right = index_from_right % 26;

    return index_from_right;
}
