#pragma once

#define UKW_B "YRUHQSLDPXNGOKMIEBFZCWVJAT"
#define UKW_C "FVPJIAOYEDRZXWGCTKUQSBNMHL"

typedef struct Reflector{
    char *wiring;
} Reflector;

Reflector *create_reflector(char *wiring);
Reflector *create_reflector_by_type(char type);

