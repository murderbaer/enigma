#include "../enigma/enigma.h"

typedef struct
{
    int cycles_counts[3];
    int rotor_positions[3];
    int rotors[3];
} CycleOfRotorSetting;

void create_cycles(void);
