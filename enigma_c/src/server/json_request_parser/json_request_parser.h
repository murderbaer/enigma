#pragma once

#include <cjson/cJSON.h>

#include "../../enigma/enigma.h"

int validate_enigma_json(const char *const json_string, EnigmaConfiguration *enigma_configuration);