#include <stdlib.h>
#include <string.h>

#include "../helper/helper.h"
#include "enigma.h"
#include "plugboard/plugboard.h"
#include "reflector/reflector.h"
#include "rotor/rotor.h"

Enigma *create_m3_enigma(Rotor *rotor_one, Rotor *rotor_two, Rotor *rotor_three,
                         Reflector *reflector, Plugboard *plugboard)
{
    return malloc(sizeof(Enigma));
}

Enigma *create_m4_enigma(Rotor *rotor_one, Rotor *rotor_two, Rotor *rotor_three,
                         Rotor *rotor_four, Reflector *reflector,
                         Plugboard *plugboard)
{
    return malloc(sizeof(Enigma));
}

/**
 * @brief This function is used to traverse the enigma machine.
 *
 * @param enigma The enigma machine to traverse.
 * @param text_in_integer The text to traverse.
 * @param array_size The size of the text.
 * @return char* The traversed text.
 */
char *traverse_m3_enigma(Enigma *enigma, int *text_in_integer, int array_size)
{
    char *output = malloc(array_size * sizeof(char) + 1);

    Rotor *rotorOne      = enigma->rotor_three;
    Rotor *rotorTwo      = enigma->rotor_two;
    Rotor *rotorThree    = enigma->rotor_one;
    Plugboard *plugboard = enigma->plugboard;
    Reflector *reflector = enigma->reflector;

    for (int i = 0; i < array_size; i++)
    {
        // #TODO: This changes the parameter, which is not good.
        text_in_integer[i] = plugboard->plugboard_data[text_in_integer[i]];
    }

    for (int i = 0; i < array_size; i++)
    {
        rotorOne->position = (rotorOne->position + 1) % 26;

        if (should_rotate(rotorOne))
        {
            rotorTwo->position = (rotorTwo->position + 1) % 26;

            if (should_rotate(rotorTwo))
            {
                rotorThree->position = (rotorThree->position + 1) % 26;
            }
        }

        int character = traverse_rotor(rotorOne, text_in_integer[i]);
        character     = traverse_rotor(rotorTwo, character);
        character     = traverse_rotor(rotorThree, character);
        character     = reflector->wiring[character];
        character     = traverse_rotor_inverse(rotorThree, character);
        character     = traverse_rotor_inverse(rotorTwo, character);
        character     = traverse_rotor_inverse(rotorOne, character);

        output[i] = character;
    }

    for (int i = 0; i < array_size; i++)
    {
        output[i] = plugboard->plugboard_data[(int)output[i]];
    }

    output[array_size] = '\0';

    return output;
}

/**
 * @brief This function is used to traverse the enigma machine.
 *
 * @param enigma The enigma machine to traverse.
 * @param text_in_integer The text to traverse.
 * @param array_size The size of the text.
 * @return char* The traversed text.
 */
char *traverse_m4_enigma(Enigma *enigma, int *text_in_integer, int array_size)
{
    return NULL;
}

/**
 * @brief This function is used to traverse the enigma machine.
 *
 * @param enigma The enigma machine to traverse.
 * @param text_in_integer The text to traverse.
 * @param array_size The size of the text.
 * @return char* The traversed text.
 */
char *traverse_enigma(Enigma *enigma)
{
    char *plaintext      = enigma->plaintext;
    int array_size       = strlen(plaintext);
    int *text_in_numbers = get_int_array_from_string(plaintext, array_size);

    if (enigma->type == M3)
    {
        return traverse_m3_enigma(enigma, text_in_numbers, array_size);
    }
    else
    {
        return traverse_m4_enigma(enigma, text_in_numbers, array_size);
    }
}