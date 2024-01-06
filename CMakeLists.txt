cmake_minimum_required(VERSION 3.15)

project(enigma VERSION 0.1.0
    DESCRIPTION "Enigma machine simulator"
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin) # We declare a variable to select what to build

# 
add_subdirectory(src)
add_executable(enigma src/main.c)
target_link_libraries(enigma enigma_lib)

# Tests
add_subdirectory(tests)
add_executable(enigma_test tests/src/main.c)

target_link_libraries(
    enigma_test
    enigma_lib
    enigma_test_lib
)

enable_testing()

add_test(
    NAME enigma_test
    COMMAND enigma_test
)
