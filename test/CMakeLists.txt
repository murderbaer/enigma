add_executable(
    enigma_test
    src/main.c
    src/helper/helper.c
    src/helper/helper.h
)

target_link_libraries(
    enigma_test
    src
    unity
)

add_test(
    NAME enigma_test
    COMMAND enigma
)