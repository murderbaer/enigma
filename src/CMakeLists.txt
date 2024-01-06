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
)

target_include_directories(enigma_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})