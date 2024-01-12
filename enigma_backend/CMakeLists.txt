add_library(enigma_lib
    src/enigma/enigma.c
    src/enigma/enigma.h
    src/enigma/rotor/rotor.c
    src/enigma/rotor/rotor.h
    src/enigma/reflector/reflector.c
    src/enigma/reflector/reflector.h
    src/enigma/plugboard/plugboard.c
    src/enigma/plugboard/plugboard.h
    src/cli/cli.c
    src/cli/cli.h
    src/helper/helper.c
    src/helper/helper.h
    src/server/server.c
    src/server/server.h
)

target_link_libraries(enigma_lib PUBLIC pthread)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif()

target_link_libraries(enigma_lib PUBLIC cjson)

target_include_directories(enigma_lib PUBLIC src)

