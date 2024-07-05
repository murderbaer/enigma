#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cyclometer.h"
#include "enigma/enigma.h"

#define TOTAL_CYCLES 26 * 26 * 26 * 3 * 2 * 1

int possible_rotor_permutations[6][3] = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                         {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

int ring_settings[3] = {0, 0, 0};

/**
 * @brief Get cycles by hopping through the rotor permutation using the next
 * index
 * @param rotor_permutation: Array containing the next index of the cycle
 * @return Cycle: A cycle of the rotor permutation
 */
Cycle get_cycle_count(int *rotor_permutation)
{
    Cycle cycle;
    cycle.length       = 0;
    cycle.cycle_values = malloc(26 * sizeof(int));

    bool visited[26] = {false};

    for (int i = 0; i < 26; i++)
    {
        if (visited[i] == false)
        {
            int base                 = i;
            visited[base]            = true;
            int current              = rotor_permutation[base];
            int current_cycle_length = 1;
            // TODO: cycles should be sorted

            while (current != base)
            {
                visited[current] = true;
                current          = rotor_permutation[current];
                current_cycle_length++;
            }

            cycle.cycle_values[cycle.length] = current_cycle_length;
            cycle.length++;
        }
    }

    return cycle;
}

void print_cycle(Cycle cycle)
{
    printf("( ");
    for (int i = 0; i < cycle.length; i++)
    {
        printf("%d", cycle.cycle_values[i]);

        if (i < cycle.length - 1)
        {
            printf(" ");
        }
    }
    printf(" )");
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

    for (int letter = 0; letter < 26; letter++)
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

    cycle->cycles[0] = get_cycle_count(rotor_one_permutation);
    cycle->cycles[1] = get_cycle_count(rotor_two_permutation);
    cycle->cycles[2] = get_cycle_count(rotor_three_permutation);

    print_cycle(cycle->cycles[0]);
    printf(" / ");
    print_cycle(cycle->cycles[1]);
    printf(" / ");
    print_cycle(cycle->cycles[2]);

    printf(": %d %d %d: ", cycle_configuration->rotor_one,
           cycle_configuration->rotor_two, cycle_configuration->rotor_three);
    printf("%d %d %d\n", configuration->rotors[0], configuration->rotors[1],
           configuration->rotors[2]);

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
                    cycle_configuration->reflector_index   = 'A';
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
}
