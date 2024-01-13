#include "json_request_parser.h"

#include "enigma/enigma.h"
#include "helper/helper.h"
#include <cjson/cJSON.h>
#include <string.h>

#define ENIGMA_TYPE_KEY "enigmaType"

#define ROTORS_KEY "rotors"
#define ROTOR_KEY "ring"
#define RING_SETTINGS_KEY "ringPosition"
#define ROTOR_SETTINGS_KEY "rotorPosition"

#define REFLECTOR_KEY "reflector"
#define PLUGBOARD_KEY "plugboard"
#define MESSAGE_KEY "message"

typedef struct EnigmaConfiguration
{
    int rotors[3];
    int enigma_type;
    int rotor_settings[3];
    int ring_settings[3];
    int reflector;
    char plugboard[26];
    char message[1024];
} EnigmaConfiguration;

int validate_enigma_type(cJSON *json)
{
    cJSON *enigma_type = cJSON_GetObjectItem(json, ENIGMA_TYPE_KEY);
    EnigmaConfiguration enigma_configuration;

    if (!enigma_type)
    {
        return 0;
    }

    char *enigma_type_value = enigma_type->valuestring;

    if (strcmp(enigma_type_value, "M3") == 0)
    {
        enigma_configuration.enigma_type = M3;
    }
    else if (strcmp(enigma_type_value, "M4") == 0)
    {
        enigma_configuration.enigma_type = M4;
    }
    else
    {
        return 0;
    }

    cJSON *rotors = cJSON_GetObjectItem(json, ROTORS_KEY);
    if (!rotors)
    {
        return 0;
    }

    cJSON *rotor = rotors->child;
    int i        = 0;
    while (rotor)
    {
        enigma_configuration.rotors[i] = rotor->valueint;
        rotor                          = rotor->next;
        i++;
    }

    cJSON *ring_settings = cJSON_GetObjectItem(json, RING_SETTINGS_KEY);
    if (!ring_settings)
    {
        return 0;
    }

    cJSON *ring_setting = ring_settings->child;
    i                   = 0;
    while (ring_setting)
    {
        enigma_configuration.ring_settings[i] = ring_setting->valueint;
        ring_setting                          = ring_setting->next;
        i++;
    }

    cJSON *rotor_settings = cJSON_GetObjectItem(json, ROTOR_SETTINGS_KEY);
    if (!rotor_settings)
    {
        return 0;
    }

    cJSON *rotor_setting = rotor_settings->child;
    i                    = 0;
    while (rotor_setting)
    {
        enigma_configuration.rotor_settings[i] = rotor_setting->valueint;
        rotor_setting                          = rotor_setting->next;
        i++;
    }

    cJSON *reflector = cJSON_GetObjectItem(json, REFLECTOR_KEY);
    if (!reflector)
    {
        return 0;
    }

    enigma_configuration.reflector = reflector->valueint;

    cJSON *plugboard = cJSON_GetObjectItem(json, PLUGBOARD_KEY);
    if (!plugboard)
    {
        return 0;
    }

    char *plugboard_value = plugboard->valuestring;
    if (strlen(plugboard_value) > 26)
    {
        return 0;
    }

    strcpy(enigma_configuration.plugboard, plugboard_value);

    cJSON *message = cJSON_GetObjectItem(json, MESSAGE_KEY);
    if (!message)
    {
        return 0;
    }

    char *message_value = message->valuestring;
    if (strlen(message_value) > 1024)
    {
        return 0;
    }

    strcpy(enigma_configuration.message, message_value);

    return 1;
}
