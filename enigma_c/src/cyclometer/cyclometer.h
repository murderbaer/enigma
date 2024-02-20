#include "../enigma/enigma.h"

typedef struct
{
    int cycle_count;
    char **cycles;
    char message_key[3];
    int rotor_positions[3];
    int rotors[3];
} Cycle;

Cycle **create_cycles(void);
