cmake_minimum_required(VERSION 3.15)

project(enigma VERSION 0.1.0
    DESCRIPTION "Enigma machine simulator"
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)

add_library(enigma_lib STATIC 
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

add_executable(enigma
    main.c 
)

target_link_libraries(enigma enigma_lib)