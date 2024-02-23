#include "../enigma/enigma.h"

typedef struct
{
    int cycle_count;
    struct Cycle *next;
} Cycle;

typedef struct
{
    Cycle cycles[3];
    char message_key[3];
    int rotor_positions[3];
    int rotors[3];
} CycleOfRotorSetting;
void create_cycles(void);
