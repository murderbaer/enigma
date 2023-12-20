#pragma once

#include "../enigma/enigma.h"

#define HELP "--help"
#define HELP_SHORT "-h"
#define INTERACTIVE "--interactive"
#define INTERACTIVE_SHORT "-i"
#define ENIGMA "--enigma"
#define ENIGMA_SHORT "-e"
#define ROTOR_ONE "--rotor-one"
#define ROTOR_ONE_SHORT "-r1"
#define ROTOR_TWO "--rotor-two"
#define ROTOR_TWO_SHORT "-r2"
#define ROTOR_THREE "--rotor-three"
#define ROTOR_THREE_SHORT "-r3"
#define ROTOR_FOUR "--rotor-four"
#define ROTOR_FOUR_SHORT "-r4"
#define ROTOR_OFFSETS "--ring-positions"
#define ROTOR_OFFSETS_SHORT "-ro"
#define ROTOR_POSITIONS "--rotor-positions"
#define ROTOR_POSITIONS_SHORT "-rp"
#define REFLECTOR "--reflector"
#define REFLECTOR_SHORT "-rf"
#define PLUGBOARD "--plugboard"
#define PLUGBOARD_SHORT "-pb"
#define PLAINTEXT "--plaintext"
#define PLAINTEXT_SHORT "-pt"

Enigma *query_input(int argc, char ** argv);
