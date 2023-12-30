cmake_minimum_required(VERSION 3.15)

project(enigma VERSION 0.1.0
                DESCRIPTION "Enigma machine simulator"
                LANGUAGES C)

set(CMAKE_C_STANDARD 17)


add_executable(enigma
    main.c
    enigma.c
    enigma.h
    enigma/rotor.c
    enigma/rotor.h
    enigma/reflector.c
    enigma/reflector.h
    enigma/plugboard.c
    enigma/plugboard.h
    cli/cli.c
    cli/cli.h
    helper/helper.c
    helper/helper.h
    server/server.c
    server/server.h
)

