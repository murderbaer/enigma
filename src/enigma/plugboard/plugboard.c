#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "plugboard.h"

int is_char_allowed_as_plugboard(char to_check)
{
    if (to_check <= 'A' || to_check >= 'Z')
    {
        return 0;
    }

    return 1;
}

Plugboard *create_plugboard(char *input)
{
    int input_length       = strlen(input);
    Plugboard *plugboard   = (Plugboard *)malloc(sizeof(Plugboard));
    int plugboard_data[26] = {-1};

    for (int i = 0; i < input_length; i++)
    {
        if (!is_char_allowed_as_plugboard(input[i]) ||
            !is_char_allowed_as_plugboard(input[i + 1]))
        {
            continue;
        }

        int input_left  = input[i] - 'A';
        int input_right = input[i + 1] - 'A';
        i++;

        if (plugboard_data[input_left] == -1 &&
            plugboard_data[input_right] == -1)
        {
            plugboard_data[input_left]  = input_right;
            plugboard_data[input_right] = input_left;
        }
        else
        {
            printf("Falsely configured plugboard. Exiting with error!");
            exit(1);
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (plugboard_data[i] == -1)
            plugboard_data[i] = i;
    }

    memcpy(plugboard->plugboard, plugboard_data, 26);

    return plugboard;
}
