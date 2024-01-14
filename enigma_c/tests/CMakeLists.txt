add_library(
    enigma_test_lib
    helper/helper.c
    helper/helper.h
    cli/cli.c
    cli/cli.h
)

add_subdirectory(libraries/unity)

target_link_libraries(
    enigma_test_lib
    enigma_lib
    unity
)
