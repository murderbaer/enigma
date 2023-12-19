#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli/cli.h"
#include "enigma/enigma.h"
#include "enigma/plugboard/plugboard.h"
#include "enigma/reflector/reflector.h"
#include "enigma/rotor/rotor.h"

typedef struct SIZED_INT_ARRAY
{
    int *array;
    int size;
} SIZED_INT_ARRAY;

int main(int argc, char **argv)
{

    Enigma *enigma = query_input(argc, argv);
    char *input    = enigma->plaintext;
    int array_size = strlen(input);
    int *int_array = malloc(array_size * sizeof(int));

    for (int i = 0; i < array_size; i++)
    {
        int_array[i] = input[i] - 'A';
    }

    char *output            = malloc(array_size * sizeof(char));
    int real_size_of_output = 0;
    Rotor *rotorOne         = enigma->rotor_one;
    Rotor *rotorTwo         = enigma->rotor_two;
    Rotor *rotorThree       = enigma->rotor_three;
    //    Rotor *rotorFour                = enigma->rotor_four;
    Reflector *reflector = enigma->reflector;
    Plugboard *plugboard = enigma->plugboard;

    printf("Input: %s\n", input);

    for (int i = 0; i < array_size; i++)
    {
        int_array[i] = plugboard->plugboard_data[int_array[i]];
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

        int character = traverse_rotor(rotorOne, int_array[i]);
        character     = traverse_rotor(rotorTwo, character);
        character     = traverse_rotor(rotorThree, character);
        character     = reflector->wiring[character];
        character     = traverse_rotor_inverse(rotorThree, character);
        character     = traverse_rotor_inverse(rotorTwo, character);
        character     = traverse_rotor_inverse(rotorOne, character);

        output[real_size_of_output] = character;
        real_size_of_output++;
    }

    for (int i = 0; i < real_size_of_output; i++)
    {
        output[i] = plugboard->plugboard_data[(int)output[i]];
    }

    for (int i = 0; i < real_size_of_output; i++)
    {
        if (i % 5 == 0 && i != 0)
        {
            //           printf(" ");
        }

        printf("%c", output[i] + 'A');
    }

    printf("\n");

    return 0;
}
