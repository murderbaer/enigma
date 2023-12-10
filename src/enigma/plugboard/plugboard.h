#pragma once

typedef struct Plugboard {
    int plugboard[26];
} Plugboard;

Plugboard *create_plugboard(char* input);
