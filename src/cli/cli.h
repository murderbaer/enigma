#pragma once

#define ALLOWED_CHARACTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

typedef struct {
    int rotor_on_position_one;
    char *rotor_on_position_one_value;
    int rotor_on_position_two;
    char *rotor_on_position_two_value;
    int rotor_on_position_three;
    char *rotor_on_position_three_value;
    int rotor_on_position_four;
    char *rotor_on_position_four_value;
    int reflector;
    char *reflector_value;
    int plugboard;
    char *plugboard_value;
    int ring_settings;
    char *ring_settings_value;
    int input;
    char *input_value;
} EnabledOptions;

typedef struct {
    char *rotors[3];
    char notches[3];
    char *reflector;
    char *ring_settings;
    char *input;
} ParsedOptions;

int checkRotorFormatting(char *rotorName);

ParsedOptions *parse_options(int argc, char **argv);
