#pragma once

typedef struct Plugboard {
    int *plugboard_data;
} Plugboard;

Plugboard *create_plugboard(char* input);
