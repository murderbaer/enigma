#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plugboard.h"

Plugboard *create_plugboard(char *input)
{
    int input_length     = strlen(input);
    Plugboard *plugboard = (Plugboard *)malloc(sizeof(Plugboard));
    int plugboard_data[26];

    for (int i = 0; i < 26; i++)
    {
        plugboard_data[i] = -1;
    }

    for (int i = 0; i < input_length; i += 2)
    {
        int input_left  = input[i] - 'A';
        int input_right = input[i + 1] - 'A';

        plugboard_data[input_left]  = input_right;
        plugboard_data[input_right] = input_left;
    }

    plugboard->plugboard_data = malloc(sizeof(int) * 26);

    for (int i = 0; i < 26; i++)
    {
        if (plugboard_data[i] == -1)
        {
            plugboard_data[i] = i;
        }
        else
        {
            plugboard_data[i] = plugboard_data[plugboard_data[i]];
        }
    }

    memcpy(plugboard->plugboard_data, plugboard_data, sizeof(int) * 26);

    return plugboard;
}
