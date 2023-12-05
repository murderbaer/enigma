#pragma once

#define ROTOR_I "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define ROTOR_I_INV "UWYGADFPVZBECKMTHXSLRINQOJ"
#define ROTOR_I_NOTCH 'Q'
#define ROTOR_II "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define ROTOR_II_INV "AJPCZWRLFBDKOTYUQGENHXMIVS"
#define ROTOR_II_NOTCH 'E'
#define ROTOR_III "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define ROTOR_III_INV "TAGBPCSDQEUFVNZHYIXJWLRKOM"
#define ROTOR_III_NOTCH 'V'

#define UKW_B "YRUHQSLDPXNGOKMIEBFZCWVJAT"

typedef struct
{
    int wiring[26];
    int inverse_wiring[26];
    int position;
    int *notch;
    int notch_count;
} Rotor;

Rotor *create_one_notch_rotor(char *wiring, char *inverse_wiring, char notch);
Rotor *create_two_notch_rotor(char *wiring, char *inverse_wiring, char notch1,
                              char notch2);
int traverse_rotor(Rotor *rotor, int character);
int traverse_rotor_inverse(Rotor *rotor, int character);
int should_rotate(Rotor *rotor);
