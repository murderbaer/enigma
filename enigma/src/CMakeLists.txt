
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -Wextra -Werror -O3 -std=c17")

add_library(enigma_lib
    cyclometer/cyclometer.c
    cyclometer/cyclometer.h
    enigma/enigma.c
    enigma/enigma.h
    enigma/rotor/rotor.c
    enigma/rotor/rotor.h
    enigma/reflector/reflector.c
    enigma/reflector/reflector.h
    enigma/plugboard/plugboard.c
    enigma/plugboard/plugboard.h
    cli/cli.c
    cli/cli.h
    helper/helper.c
    helper/helper.h
    server/server.c
    server/server.h
    server/json_request_parser/json_request_parser.c
    server/json_request_parser/json_request_parser.h
)

target_link_libraries(enigma_lib PUBLIC pthread)

target_link_libraries(enigma_lib PUBLIC cjson)

target_include_directories(enigma_lib PUBLIC .)
