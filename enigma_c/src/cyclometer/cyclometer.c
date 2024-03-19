#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cyclometer.h"
#include "enigma/enigma.h"

#define TOTAL_CYCLES 26 * 26 * 26 * 3 * 2 * 1

int possible_rotor_permutations[6][3] = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                         {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

typedef struct CycleConfiguration
{
    int rotor_one;
    int rotor_two;
    int rotor_three;
    int rotor_permutation;
    char reflector_index;
} CycleConfiguration;

int ring_settings[3] = {0, 0, 0};

int get_cycle_count(int *permutaion)
{
    int number_of_cycles = 0;
    int visted[26]       = {0};

    for (int i = 0; i < 26; i++)
    {
        if (visted[i] == 0)
        {
            number_of_cycles++;
            int j = i;
            while (visted[j] == 0)
            {
                visted[j] = 1;
                j         = permutaion[j];
            }
        }
    }

    return number_of_cycles;
}

CycleOfRotorSetting *create_cycle(CycleConfiguration *cycle_configuration,
                                  int *rotor_permutation)
{
    CycleOfRotorSetting *cycle = malloc(sizeof(CycleOfRotorSetting));

    EnigmaConfiguration *configuration = malloc(sizeof(EnigmaConfiguration));
    configuration->type                = M3;
    configuration->rotors              = malloc(3 * sizeof(int));
    configuration->rotor_positions     = malloc(3 * sizeof(int));
    configuration->ring_settings       = ring_settings;

    configuration->rotor_positions[0] = cycle_configuration->rotor_one;
    configuration->rotor_positions[1] = cycle_configuration->rotor_two;
    configuration->rotor_positions[2] = cycle_configuration->rotor_three;
    cycle->rotor_positions[0]         = cycle_configuration->rotor_one;
    cycle->rotor_positions[1]         = cycle_configuration->rotor_two;
    cycle->rotor_positions[2]         = cycle_configuration->rotor_three;

    configuration->ring_settings[0] = 0;
    configuration->ring_settings[1] = 0;
    configuration->ring_settings[2] = 0;
    // FIXME: Rotor 1,1,1 should not be possible, values have to be unique
    configuration->rotors[0] = rotor_permutation[0];
    configuration->rotors[1] = rotor_permutation[1];
    configuration->rotors[2] = rotor_permutation[2];
    cycle->rotors[0]         = rotor_permutation[0];
    cycle->rotors[1]         = rotor_permutation[1];
    cycle->rotors[2]         = rotor_permutation[2];

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

    cycle->cycles_counts[0] = get_cycle_count(rotor_one_permutation);
    cycle->cycles_counts[1] = get_cycle_count(rotor_two_permutation);
    cycle->cycles_counts[2] = get_cycle_count(rotor_three_permutation);

    free(configuration->rotor_positions);
    free(configuration->rotors);
    free(configuration);

    return cycle;
}

void create_cycles(void)
{
    // 3 rotors and 26 possible settings for each rotor, 5 * 4 * 3 rotor
    // permutations, 2 reflectors
    CycleOfRotorSetting **cycles =
        malloc(TOTAL_CYCLES * sizeof(CycleOfRotorSetting));
    int iterations = 0;

    for (int rotor_one = 0; rotor_one < 26; rotor_one++)
    {
        for (int rotor_two = 0; rotor_two < 26; rotor_two++)
        {
            for (int rotor_three = 0; rotor_three < 26; rotor_three++)
            {
                for (int rotor_permutation = 0; rotor_permutation < 3 * 2 * 1;
                     rotor_permutation++)
                {

                    CycleConfiguration *cycle_configuration =
                        malloc(sizeof(CycleConfiguration));
                    cycle_configuration->rotor_one         = rotor_one;
                    cycle_configuration->rotor_two         = rotor_two;
                    cycle_configuration->rotor_three       = rotor_three;
                    cycle_configuration->rotor_permutation = rotor_permutation;
                    cycle_configuration->reflector_index   = 'B';
                    cycles[iterations]                     = create_cycle(
                        cycle_configuration,
                        possible_rotor_permutations[rotor_permutation]);
                    iterations++;
                }
            }
        }
    }

    for (int i = 0; i < TOTAL_CYCLES; i++)
    {
        free(cycles[i]);
    }

    free(cycles);
    printf("Total cycles: %d\n", TOTAL_CYCLES);
}
