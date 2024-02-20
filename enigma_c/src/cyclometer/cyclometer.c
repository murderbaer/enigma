#include <stdio.h>
#include <stdlib.h>

#include "../helper/helper.h"
#include "cyclometer.h"
#include "enigma/enigma.h"
#include "enigma/plugboard/plugboard.h"

typedef struct CycleConfiguration
{
    Cycle *cycle;
    int rotor_one;
    int rotor_two;
    int rotor_three;
    int rotor_permutation;
    int reflector_index;
    char message_key[3];
} CycleConfiguration;

void create_cycle(CycleConfiguration *cycle_configuration)
{

    for (int letter = 0; letter < 26; letter++)
    {
        EnigmaConfiguration *configuration =
            malloc(sizeof(EnigmaConfiguration));
        configuration->type            = M3;
        configuration->rotors          = malloc(3 * sizeof(int));
        configuration->rotor_positions = malloc(3 * sizeof(int));

        int ring_settings[3]         = {0, 0, 0};
        configuration->ring_settings = ring_settings;

        for (int i = 0; i < 26; i++)
        {
            configuration->plugboard[i] = i + 'A';
        }

        configuration->rotor_positions[0] = cycle_configuration->rotor_one;
        configuration->rotor_positions[1] = cycle_configuration->rotor_two;
        configuration->rotor_positions[2] = cycle_configuration->rotor_three;

        configuration->ring_settings[0] = 0;
        configuration->ring_settings[1] = 0;
        configuration->ring_settings[2] = 0;

        configuration->rotors[0] =
            cycle_configuration->rotor_permutation / 12 + 1;
        configuration->rotors[1] =
            (cycle_configuration->rotor_permutation / 3) % 4 + 1;
        configuration->rotors[2] =
            cycle_configuration->rotor_permutation % 3 + 1;

        configuration->reflector = cycle_configuration->reflector_index;

        configuration->message[0] = letter + 'A';
        configuration->message[1] = letter + 'A';
        configuration->message[2] = letter + 'A';
        configuration->message[3] = letter + 'A';
        configuration->message[4] = letter + 'A';
        configuration->message[5] = letter + 'A';
        configuration->message[6] = '\0';

        Enigma *enigma = create_enigma_from_configuration(configuration);

        int *output         = traverse_enigma(enigma);
        char *output_string = get_string_from_int_array(output, 6);

        cycle_configuration->cycle = malloc(sizeof(Cycle));

        cycle_configuration->cycle->message_key[0] = letter + 'A';
        cycle_configuration->cycle->message_key[1] = letter + 'A';
        cycle_configuration->cycle->message_key[2] = letter + 'A';
        cycle_configuration->cycle->rotors[0]      = configuration->rotors[0];
        cycle_configuration->cycle->rotors[1]      = configuration->rotors[1];
        cycle_configuration->cycle->rotors[2]      = configuration->rotors[2];

        free(output);
        free(output_string);
        free_enigma(enigma);
        free(configuration->rotor_positions);
        free(configuration->rotors);
        free(configuration);
    }

    free(cycle_configuration);
}

Cycle **create_cycles(void)
{
    // 3 rotors and 26 possible settings for each rotor, 5 * 4 * 3 rotor
    // permutations, 2 reflectors
    int total_cycles = 26 * 26 * 26 * 5 * 4 * 3 * 2;
    Cycle **cycles   = malloc(total_cycles * sizeof(Cycle *));
    int iterations   = 0;

    for (int rotor_one = 0; rotor_one < 26; rotor_one++)
    {
        for (int rotor_two = 0; rotor_two < 26; rotor_two++)
        {
            for (int rotor_three = 0; rotor_three < 26; rotor_three++)
            {
                for (int rotor_permutation = 0; rotor_permutation < 5 * 4 * 3;
                     rotor_permutation++)
                {
                    for (int reflector_index = 0; reflector_index < 2;
                         reflector_index++)
                    {
                        CycleConfiguration *cycle_configuration =
                            malloc(sizeof(CycleConfiguration));
                        cycle_configuration->cycle       = cycles[iterations];
                        cycle_configuration->rotor_one   = rotor_one;
                        cycle_configuration->rotor_two   = rotor_two;
                        cycle_configuration->rotor_three = rotor_three;
                        cycle_configuration->rotor_permutation =
                            rotor_permutation;
                        cycle_configuration->reflector_index = reflector_index;
                        create_cycle(cycle_configuration);
                        iterations++;
                    }
                }
            }
        }
    }

    printf("Total cycles: %d\n", iterations);

    return cycles;
}
