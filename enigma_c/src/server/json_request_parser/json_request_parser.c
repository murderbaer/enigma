#include <cjson/cJSON.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../../helper/helper.h"
#include "json_request_parser.h"

#define ENIGMA_TYPE_KEY "enigmaType"

#define ROTORS_KEY "rotors"
#define ROTOR_KEY "ring"
#define RING_SETTINGS_KEY "ringSettings"
#define ROTOR_POSITIONS_KEY "rotorPositions"

#define REFLECTOR_KEY "reflector"
#define PLUGBOARD_KEY "plugboard"
#define MESSAGE_KEY "message"

int validate_enigma_json(const char *const json_string,
                         EnigmaConfiguration *enigma_configuration)
{
    cJSON *json = cJSON_Parse(json_string);
    if (json == NULL)
    {
        return 0;
    }

    cJSON *enigma_type =
        cJSON_GetObjectItemCaseSensitive(json, ENIGMA_TYPE_KEY);
    if (cJSON_IsString(enigma_type) == 0)
    {
        return 0;
    }
    else
    {
        if (strcmp(enigma_type->valuestring, "M3") == 0)
        {
            enigma_configuration->type = M3;
        }
        else if (strcmp(enigma_type->valuestring, "M4") == 0)
        {
            enigma_configuration->type = M4;
        }
        else
        {
            return 0;
        }

        enigma_configuration->rotors =
            malloc(sizeof(int) * enigma_configuration->type);
        enigma_configuration->ring_settings =
            malloc(sizeof(int) * enigma_configuration->type);
        enigma_configuration->rotor_positions =
            malloc(sizeof(int) * enigma_configuration->type);
    }

    cJSON *rotors = cJSON_GetObjectItemCaseSensitive(json, ROTORS_KEY);
    if (cJSON_IsArray(rotors) == 0)
    {
        return 0;
    }

    int i = 0;

    cJSON *rotor = NULL;
    cJSON_ArrayForEach(rotor, rotors)
    {
        if (cJSON_IsNumber(rotor) == 0)
        {
            return 0;
        }

        enigma_configuration->rotors[i] = rotor->valueint;
        i++;
    }

    cJSON *ring_settings =
        cJSON_GetObjectItemCaseSensitive(json, RING_SETTINGS_KEY);
    if (cJSON_IsString(ring_settings) == 0)
    {
        return 0;
    }
    else
    {
        for (size_t j = 0; j < strlen(ring_settings->valuestring); j++)
        {
            if (ring_settings->valuestring[j] < 'A' ||
                ring_settings->valuestring[j] > 'Z')
            {
                return 0;
            }

            enigma_configuration->ring_settings[j] =
                ring_settings->valuestring[j] - 'A';
        }
    }

    cJSON *rotor_positions =
        cJSON_GetObjectItemCaseSensitive(json, ROTOR_POSITIONS_KEY);
    if (cJSON_IsString(rotor_positions) == 0)
    {
        return 0;
    }
    else
    {
        for (size_t j = 0; j < strlen(rotor_positions->valuestring); j++)
        {
            if (rotor_positions->valuestring[j] < 'A' ||
                rotor_positions->valuestring[j] > 'Z')
            {
                return 0;
            }

            enigma_configuration->rotor_positions[j] =
                rotor_positions->valuestring[j] - 'A';
        }
    }

    cJSON *reflector = cJSON_GetObjectItemCaseSensitive(json, REFLECTOR_KEY);
    if (cJSON_IsString(reflector) == 0)
    {
        return 0;
    }
    else
    {
        if (strcmp(reflector->valuestring, "B") == 0)
        {
            enigma_configuration->reflector = 'B';
        }
        else if (strcmp(reflector->valuestring, "C") == 0)
        {
            enigma_configuration->reflector = 'C';
        }
        else
        {
            return 0;
        }
    }

    cJSON *plugboard = cJSON_GetObjectItemCaseSensitive(json, PLUGBOARD_KEY);
    if (cJSON_IsString(plugboard) == 0)
    {
        return 0;
    }
    else
    {
        int plugboard_length = strlen(plugboard->valuestring);
        for (int j = 0; j < plugboard_length && j < 26; j++)
        {
            if (plugboard->valuestring[j] < 'A' ||
                plugboard->valuestring[j] > 'Z')
            {
                return 0;
            }

            enigma_configuration->plugboard[j] = plugboard->valuestring[j];
        }
    }

    cJSON *message = cJSON_GetObjectItemCaseSensitive(json, MESSAGE_KEY);
    if (cJSON_IsString(message) == 0)
    {
        return 0;
    }
    else
    {
        strncpy(enigma_configuration->message, message->valuestring,
                strlen(message->valuestring));
    }

    return 1;
}