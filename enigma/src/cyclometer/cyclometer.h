#include "../enigma/enigma.h"

typedef struct Cycle
{
    int length;
    int *cycle_values;
} Cycle;

typedef struct
{
    Cycle cycles[3];
    int rotor_positions[3];
    int rotors[3];
} CycleOfRotorSetting;

typedef struct CycleConfiguration
{
    int rotor_one;
    int rotor_two;
    int rotor_three;
    int rotor_permutation;
    char reflector_index;
} CycleConfiguration;

void create_cycles(void);
