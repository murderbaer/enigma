#pragma once

#define ROTOR_I "EKMFLGDQVZNTOWYHXUSPAIBRCJ"
#define ROTOR_I_INV "UWYGADFPVZBECKMTHXSLRINQOJ"
#define ROTOR_II "AJDKSIRUXBLHWTMCQGZNPYFVOE"
#define ROTOR_II_INV "AJPCZWRLFBDKOTYUQGENHXMIVS"
#define ROTOR_III "BDFHJLCPRTXVZNYEIWGAKMUSQO"
#define ROTOR_III_INV "TAGBPCSDQEUFVNZHYIXJWLRKOM"

#define UKW_B "YRUHQSLDPXNGOKMIEBFZCWVJAT"

typedef struct {
    int wiring[26];
    int inverse_wiring[26];
    int position;
} Rotor;

Rotor *create_rotor(char *wiring, char *inverse_wiring);
int traverse_rotor(Rotor *rotor, int character);
int traverse_rotor_inverse(Rotor *rotor, int character);
