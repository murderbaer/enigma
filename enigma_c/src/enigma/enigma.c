#include <stdio.h>
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
 * @return int* The traversed text as an integer array.
 */
int *traverse_m3_enigma(Enigma *enigma, int *text_in_integer, int array_size)
{
    int *output = malloc(array_size * sizeof(int) + 1);
    int text[array_size];

    for (int i = 0; i < array_size; i++)
    {
        text[i] = text_in_integer[i];
    }

    Rotor *rotorOne   = enigma->rotors[0];
    Rotor *rotorTwo   = enigma->rotors[1];
    Rotor *rotorThree = enigma->rotors[2];

    Plugboard *plugboard = enigma->plugboard;
    Reflector *reflector = enigma->reflector;

    for (int i = 0; i < array_size; i++)
    {
        text[i] = plugboard->plugboard_data[text[i]];
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

        int character = traverse_rotor(rotorOne, text[i]);
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
int *traverse_m4_enigma(Enigma *enigma, int *text_in_integer, int array_size)
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
int *traverse_enigma(Enigma *enigma)
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

/**
 * @brief This function is used to create an enigma machine.
 *
 * @param enigma_configuration The configuration of the enigma machine.
 * @return Enigma* The created enigma machine.
 */
Enigma *
create_enigma_from_configuration(EnigmaConfiguration *enigma_configuration)
{
    Enigma *enigma = malloc(sizeof(Enigma));

    enigma->type = enigma_configuration->type;

    enigma->rotors = malloc(sizeof(Rotor) * enigma->type);

    for (int i = 0; i < enigma->type; i++)
    {
        int rotor_type    = enigma_configuration->rotors[i];
        int position      = enigma_configuration->rotor_positions[i];
        int offset        = enigma_configuration->ring_settings[i];
        Rotor *rotor      = create_rotor(rotor_type, position, offset);
        enigma->rotors[i] = rotor;
    }

    enigma->reflector =
        create_reflector_by_type(enigma_configuration->reflector);
    enigma->plugboard = create_plugboard(enigma_configuration->plugboard);
    enigma->plaintext = enigma_configuration->message;

    return enigma;
}