#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rotor/rotor.h"
#include "ukw/ukw.h"

typedef struct SIZED_INT_ARRAY
{
    int *array;
    int size;
} SIZED_INT_ARRAY;

SIZED_INT_ARRAY string_to_int_array(char *string)
{
    SIZED_INT_ARRAY array_with_size;
    array_with_size.size  = strlen(string);
    array_with_size.array = malloc(array_with_size.size * sizeof(int));

    for (int i = 0; i < array_with_size.size; i++)
    {
        array_with_size.array[i] = string[i] - 'A';
    }

    return array_with_size;
}

int main(void)
{
    int notches[] = {
        ('Q' - 'A'),
        ('E' - 'A'),
        ('V' - 'A'),
    };

    Rotor *rotorOne   = create_one_notch_rotor(ROTOR_I, ROTOR_I_INV, 'Q');
    Rotor *rotorTwo   = create_one_notch_rotor(ROTOR_II, ROTOR_II_INV, 'E');
    Rotor *rotorThree = create_one_notch_rotor(ROTOR_III, ROTOR_III_INV, 'V');
    UKW *reflector    = create_ukw(UKW_B);

    char input[1000];
    printf("Plain text: ");
    scanf("%[^\n]s", input);
    SIZED_INT_ARRAY array_with_size = string_to_int_array(input);
    int *int_array                  = array_with_size.array;
    int array_size                  = array_with_size.size;
    char *output                    = malloc(array_size * sizeof(char));
    int real_size_of_output         = 0;

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

        output[real_size_of_output] = character + 'a';
        real_size_of_output++;
    }

    for (int i = 0; i < real_size_of_output; i++)
    {
        if (i % 5 == 0 && i != 0)
        {
            printf(" ");
        }

        printf("%c", output[i]);
    }

    printf("\n");

    return 0;
}
