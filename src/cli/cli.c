#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../enigma/rotor.h"
#include "../helper/helper.h"
#include "cli.h"

EnabledOptions createEnabledOptionsObject(void) {
    EnabledOptions enabledOptions;
    enabledOptions.rotor_on_position_one = 0;
    enabledOptions.rotor_on_position_two = 0;
    enabledOptions.rotor_on_position_three = 0;
    enabledOptions.rotor_on_position_four = 0;
    enabledOptions.reflector = 0;
    enabledOptions.plugboard = 0;
    enabledOptions.ring_settings = 0;
    enabledOptions.input = 0;

    return enabledOptions;
}

int checkRotorFormatting(char *rotorName) {
    if (strlen(rotorName) != 26) {
        return 0;
    }

    for (int i = 0; i < 26; i++) {
        if (!isupper(rotorName[i])) {
            return 0;
        }
    }

    // check for duplicates
    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (rotorName[i] == rotorName[j]) {
                return 0;
            }
        }
    }

    return 1;
}

int romanToArabicNumeral(char *romanNumeral) {
    int romanNumeralLength = strlen(romanNumeral);
    int arabicNumeral = 0;

    for (int i = 0; i < romanNumeralLength; i++) {
        switch (romanNumeral[i]) {
        case 'I':
            arabicNumeral += 1;
            break;
        case 'V':
            arabicNumeral += 5;
            break;
        case 'X':
            arabicNumeral += 10;
            break;
        case 'L':
            arabicNumeral += 50;
            break;
        case 'C':
            arabicNumeral += 100;
            break;
        case 'D':
            arabicNumeral += 500;
            break;
        case 'M':
            arabicNumeral += 1000;
            break;
        default:
            printf("Unknown roman numeral: %c\n", romanNumeral[i]);
            exit(1);
        }
    }

    return arabicNumeral;
}

char *parseRotorOptions(int rotooPosition, char *rotorName) {
    char *fullRotorName = malloc(sizeof(char) * ROTOR_SIZE);

    int rotorNameLength = strlen(rotorName);

    if (rotorNameLength > 0 && rotorNameLength < 26) {
        switch (romanToArabicNumeral(rotorName)) {
        case 1:
            return ROTOR_ONE;
        case 2:
            return ROTOR_TWO;
        case 3:
            return ROTOR_THREE;
        case 4:
            return ROTOR_FOUR;
        case 5:
            return ROTOR_FIVE;
        case 6:
            return ROTOR_SIX;
        case 7:
            return ROTOR_SEVEN;
        case 8:
            return ROTOR_EIGHT;

        default:
            printf("Unknown rotor: %s\n", rotorName);
            exit(1);
        }
    } else if (rotorNameLength == 26) {
        if (checkRotorFormatting(rotorName)) {
            fullRotorName = rotorName;
        } else {
            printf("Rotor %d is not formatted correctly.\n", rotooPosition);
            exit(1);
        }
    } else {
        printf("Rotor %d is not formatted correctly.\n", rotooPosition);
        exit(1);
    }

    return fullRotorName;
}

void printHelp(void) {
    printf("Usage: enigma [OPTION]...\n");
    printf("Encrypts or decrypts a message using the Enigma machine.\n");
    printf("\n");
    printf("  -h,  --help\t");
    printf("Prints this help message.\n");
    printf("  -r1, --rotor-one\t");
    printf("Sets the rotor on position one.\n");
    printf("  -r2, --rotor-two\t");
    printf("Sets the rotor on position two.\n");
    printf("  -r3, --rotor-three\t");
    printf("Sets the rotor on position three.\n");
    printf("  -r4, --rotor-four\t");
    printf("(Optional) Sets the rotor on position four.\n");
    printf("  -rf, --reflector\t");
    printf("Sets the reflector.\n");
    printf("  -pb, --plugboard\t");
    printf("(Optional) Sets the plugboard.\n");
    printf("  -rs, --ring-settings\t");
    printf("Sets the ring settings.\n");
    printf("  -i,  --input\t");
    printf("Text to de/encrypt Sets the input.\n");
    printf("\n");
    printf("Possible values for rotors: I, II, III, IV, V, VI, VII, VIII or a string of 26 unique capitalized characters representing the wiring of the rotor.\n\n");
    printf("Possible values for reflectors: A, B or C\n\n");
    printf("Possible values for ring settings: a string of 3 (or 4, if 4 Rotors were defined) capitalized characters representing the ring settings of the rotors.\n\n");
    printf("Possible values for plugboard: a string of 26 unique capitalized characters representing the wiring of the plugboard.\n");

    exit(0);
}

char *parseReflectorOptions(char *reflectorName) {
    if (strcmp(reflectorName, "A") == 0) {
        return REFLECTOR_A;
    } else if (strcmp(reflectorName, "B") == 0) {
        return REFLECTOR_B;
    } else if (strcmp(reflectorName, "C") == 0) {
        return REFLECTOR_C;
    } else {
        printf("Unknown reflector: %s\n", reflectorName);
        exit(1);
    }
}

ParsedOptions *parse_enabled_options(EnabledOptions enabledOptions) {

    ParsedOptions *parsedOptions = malloc(sizeof(ParsedOptions));

    char *reflector = parseReflectorOptions(enabledOptions.reflector_value);

    parsedOptions->rotor_on_position_one = parseRotorOptions(1, enabledOptions.rotor_on_position_one_value);
    parsedOptions->rotor_on_position_two = parseRotorOptions(2, enabledOptions.rotor_on_position_two_value);
    parsedOptions->rotor_on_position_three = parseRotorOptions(3, enabledOptions.rotor_on_position_three_value);
    parsedOptions->reflector = reflector;
    parsedOptions->ring_settings = enabledOptions.ring_settings_value;
    parsedOptions->input = enabledOptions.input_value;

    return parsedOptions;
}

ParsedOptions *parse_options(int argc, char **argv) {
    if (argc == 2) {
        printHelp();
    }

    if (argc + 1 % 2 == 0) {
        printf("Invalid number of arguments.\n");
        exit(1);
    }

    EnabledOptions enabledOptions = createEnabledOptionsObject();

    int i = 1;

    enabledOptions.rotor_on_position_four_value = "EMPTY";

    while (i < argc) {
        if (strncmp("-r1", argv[i], 3) == 0 || strncmp("--rotor-one", argv[i], 12) == 0) {
            enabledOptions.rotor_on_position_one = 1;
            enabledOptions.rotor_on_position_one_value = parseRotorOptions(1, argv[i + 1]);
            i += 2;
        } else if (strncmp("-r2", argv[i], 3) == 0 || strncmp("--rotor-two", argv[i], 12) == 0) {
            enabledOptions.rotor_on_position_two = 1;
            enabledOptions.rotor_on_position_two_value = parseRotorOptions(2, argv[i + 1]);
            i += 2;
        } else if (strncmp("-r3", argv[i], 3) == 0 || strncmp("--rotor-three", argv[i], 14) == 0) {
            enabledOptions.rotor_on_position_three = 1;
            enabledOptions.rotor_on_position_three_value = parseRotorOptions(3, argv[i + 1]);
            i += 2;
        } else if (strncmp("-rf", argv[i], 3) == 0 || strncmp("--reflector", argv[i], 12) == 0) {
            enabledOptions.reflector = 1;
            enabledOptions.reflector_value = argv[i + 1];
            i += 2;
        } else if (strncmp("-p", argv[i], 2) == 0 || strncmp("--plugboard", argv[i], 12) == 0) {
            enabledOptions.plugboard = 1;
            enabledOptions.plugboard_value = argv[i + 1];
            i += 2;
        } else if (strncmp("-rs", argv[i], 3) == 0 || strncmp("--ring-settings", argv[i], 16) == 0) {
            enabledOptions.ring_settings = 1;
            enabledOptions.ring_settings_value = argv[i + 1];
            i += 2;
        } else if (strncmp("-i", argv[i], 2) == 0 || strncmp("--input", argv[i], 8) == 0) {
            enabledOptions.input = 1;
            enabledOptions.input_value = argv[i + 1];
            i += 2;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            exit(1);
        }
    }

    if (enabledOptions.rotor_on_position_one == 0 ||
        enabledOptions.rotor_on_position_two == 0 ||
        enabledOptions.rotor_on_position_three == 0 ||
        enabledOptions.reflector == 0 ||
        enabledOptions.ring_settings == 0) {
        printf("Rotor on position one is not set.\n");
        exit(1);
    }

    ParsedOptions *parsedOptions = parse_enabled_options(enabledOptions);

    return parsedOptions;
}
