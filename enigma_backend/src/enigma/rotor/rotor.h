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
#define ROTOR_IV "ESOVPZJAYQUIRHXLNFTGKDCMWB"
#define ROTOR_IV_INV "HZWVARTNLGUPXQCEJMBSKDYOIF"
#define ROTOR_IV_NOTCH 'J'
#define ROTOR_V "VZBRGITYUPSDNHLXAWMJQOFECK"
#define ROTOR_V_INV "QCYLXWENFTZOSMVJUDKGIARPHB"
#define ROTOR_V_NOTCH 'Z'

#define ROTOR_VI "JPGVOUMFYQBENHZRDKASXLICTW"
#define ROTOR_VI_INV "SKXQLHCNWARVGMEBJPTYFDZUIO"
#define ROTOR_VI_NOTCH_ONE 'Z'
#define ROTOR_VI_NOTCH_TWO 'M'
#define ROTOR_VII "NZJHGRCXMYSWBOUFAIVLPEKQDT"
#define ROTOR_VII_INV "QMGYVPEDRCWTIANUXFKZOSLHJB"
#define ROTOR_VII_NOTCH_ONE 'Z'
#define ROTOR_VII_NOTCH_TWO 'M'
#define ROTOR_VIII "FKQHTLXOCBJSPDZRAMEWNIUYGV"
#define ROTOR_VIII_INV "QJINSAYDVKBFRUHMCPLEWZTGXO"
#define ROTOR_VIII_NOTCH_ONE 'Z'
#define ROTOR_VIII_NOTCH_TWO 'M'

typedef struct
{
    int wiring[26];
    int inverse_wiring[26];
    int position;
    int *notch;
    int notch_count;
    int offset;
} Rotor;

Rotor *create_one_notch_rotor(char *wiring, char *inverse_wiring, char notch, int position, int offset);
Rotor *create_two_notch_rotor(char *wiring, char *inverse_wiring, char notch1,
                              char notch2);
Rotor *create_rotor(int type, int postion, int offset);
int traverse_rotor(Rotor *rotor, int character);
int traverse_rotor_inverse(Rotor *rotor, int character);
int should_rotate(Rotor *rotor);
