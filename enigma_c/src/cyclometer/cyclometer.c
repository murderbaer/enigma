#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helper/helper.h"
#include "cyclometer.h"
#include "enigma/enigma.h"
#include "enigma/plugboard/plugboard.h"

typedef struct CycleConfiguration
{
    int rotor_one;
    int rotor_two;
    int rotor_three;
    int rotor_permutation;
    char reflector_index;
} CycleConfiguration;

int ring_settings[3] = {0, 0, 0};

void create_cycles_from_permutaion(int *permutaion, CycleOfRotorSetting *cycle,
                                   int rotor)
{
}

CycleOfRotorSetting *create_cycle(CycleConfiguration *cycle_configuration)
{
    CycleOfRotorSetting *cycle = malloc(sizeof(CycleOfRotorSetting));
    cycle->rotors[0]           = cycle_configuration->rotor_one;
    cycle->rotors[1]           = cycle_configuration->rotor_two;
    cycle->rotors[2]           = cycle_configuration->rotor_three;

    EnigmaConfiguration *configuration = malloc(sizeof(EnigmaConfiguration));
    configuration->type                = M3;
    configuration->rotors              = malloc(3 * sizeof(int));
    configuration->rotor_positions     = malloc(3 * sizeof(int));
    configuration->ring_settings       = ring_settings;

    configuration->rotor_positions[0] = cycle_configuration->rotor_one;
    configuration->rotor_positions[1] = cycle_configuration->rotor_two;
    configuration->rotor_positions[2] = cycle_configuration->rotor_three;
    configuration->ring_settings[0]   = 0;
    configuration->ring_settings[1]   = 0;
    configuration->ring_settings[2]   = 0;
    // FIXME: Rotor 1,1,1 should not be possible, values have to be unique
    configuration->rotors[0] = cycle_configuration->rotor_permutation / 12 + 1;
    configuration->rotors[1] =
        (cycle_configuration->rotor_permutation / 3) % 4 + 1;
    configuration->rotors[2] = cycle_configuration->rotor_permutation % 3 + 1;
    configuration->reflector = cycle_configuration->reflector_index;

    for (int i = 0; i < 26; i++)
    {
        configuration->plugboard[i] = i + 'A';
    }

    int rotor_one_permutation[26]   = {0};
    int rotor_two_permutation[26]   = {0};
    int rotor_three_permutation[26] = {0};

    for (int letter = 1; letter < 26; letter++)
    {
        configuration->message[0] = letter + 'A';
        configuration->message[1] = letter + 'A';
        configuration->message[2] = letter + 'A';
        configuration->message[3] = letter + 'A';
        configuration->message[4] = letter + 'A';
        configuration->message[5] = letter + 'A';
        configuration->message[6] = '\0';

        Enigma *enigma = create_enigma_from_configuration(configuration);

        int *output                        = traverse_enigma(enigma);
        rotor_one_permutation[output[0]]   = output[3];
        rotor_two_permutation[output[1]]   = output[4];
        rotor_three_permutation[output[2]] = output[5];

        free(output);
        free_enigma(enigma);
    }

    create_cycles_from_permutaion(rotor_one_permutation, cycle, 0);
    create_cycles_from_permutaion(rotor_two_permutation, cycle, 1);
    create_cycles_from_permutaion(rotor_three_permutation, cycle, 2);

    free(configuration->rotor_positions);
    free(configuration->rotors);
    free(configuration);

    return cycle;
}

void create_cycles(void)
{
    // 3 rotors and 26 possible settings for each rotor, 5 * 4 * 3 rotor
    // permutations, 2 reflectors
    int total_cycles = 26 * 26 * 26 * 5 * 4 * 3 * 2;
    CycleOfRotorSetting **cycles =
        malloc(total_cycles * sizeof(CycleOfRotorSetting));
    int iterations = 0;

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
                        cycle_configuration->rotor_one   = rotor_one;
                        cycle_configuration->rotor_two   = rotor_two;
                        cycle_configuration->rotor_three = rotor_three;
                        cycle_configuration->rotor_permutation =
                            rotor_permutation;
                        cycle_configuration->reflector_index =
                            reflector_index + 'B';
                        cycles[iterations] = create_cycle(cycle_configuration);
                        iterations++;
                    }
                }
            }
        }
    }

    for (int i = 0; i < total_cycles; i++)
    {
        free(cycles[i]);
    }

    printf("Total cycles: %d\n", iterations);
}
