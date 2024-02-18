#include <stdio.h>
#include <stdlib.h>

#include "../helper/helper.h"
#include "cyclometer.h"
#include "enigma/enigma.h"
#include "enigma/plugboard/plugboard.h"

Cycle *create_cycles(void)
{
    int total_cycles                   = 26 * 26 * 26 * 6;
    Cycle *cycles                      = malloc(total_cycles * sizeof(Cycle));
    EnigmaConfiguration *configuration = malloc(sizeof(EnigmaConfiguration));
    configuration->type                = M3;
    configuration->rotors              = malloc(3 * sizeof(int));
    configuration->rotor_positions     = malloc(3 * sizeof(int));

    int ring_settings[3]         = {0, 0, 0};
    configuration->ring_settings = ring_settings;

    for (int i = 0; i < 26; i++)
    {
        configuration->plugboard[i] = i + 'A';
    }

    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            for (int k = 0; k < 26; k++)
            {
                configuration->rotor_positions[0] = i;
                configuration->rotor_positions[1] = j;
                configuration->rotor_positions[2] = k;

                // set rotors
                for (int l = 0; l < 5 * 4 * 3; l++)
                {
                    configuration->rotors[0] = l / 12 + 1;
                    configuration->rotors[1] = (l / 3) % 4 + 1;
                    configuration->rotors[2] = l % 3 + 1;

                    for (int m = 0; m < 26; m++)
                    {
                        for (int n = 0; n < 2; n++)
                        {
                            char reflector = n == 0 ? 'B' : 'C';

                            configuration->reflector = reflector;

                            configuration->message[0] = m + 'A';
                            configuration->message[1] = m + 'A';
                            configuration->message[2] = m + 'A';
                            configuration->message[3] = m + 'A';
                            configuration->message[4] = m + 'A';
                            configuration->message[5] = m + 'A';

                            Enigma *enigma =
                                create_enigma_from_configuration(configuration);
                            int *traversed_text = traverse_enigma(enigma);
                            char *traversed_text_string =
                                get_string_from_int_array(traversed_text, 6);

                            printf("%c %c %c %c %c %s\n", i + 'A', j + 'A',
                                   k + 'A', m + 'A', reflector,
                                   traversed_text_string);

                            free(traversed_text);
                            free(traversed_text_string);
                            free(enigma->rotors[0]->notch);
                            free(enigma->rotors[0]);
                            free(enigma->rotors[1]->notch);
                            free(enigma->rotors[1]);
                            free(enigma->rotors[2]->notch);
                            free(enigma->rotors[2]);
                            free(enigma->rotors);
                            free(enigma->plugboard->plugboard_data);
                            free(enigma->plugboard);
                            free(enigma->reflector->wiring);
                            free(enigma->reflector);
                            free(enigma);
                        }
                    }
                }
            }
        }
    }

    free(configuration->rotors);
    free(configuration->rotor_positions);
    free(configuration);

    return cycles;
}
