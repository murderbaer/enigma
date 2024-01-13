add_library(enigma_lib
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

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif()

target_link_libraries(enigma_lib PUBLIC cjson)

target_include_directories(enigma_lib PUBLIC .)
