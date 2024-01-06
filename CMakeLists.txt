cmake_minimum_required(VERSION 3.15)

project("Enigma ABC" C)

set(CMAKE_C_STANDARD 17)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin) # We declare a variable to select what to build

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(libraries/unity)

add_executable(Enigma src/main.c)

target_link_libraries(Enigma PUBLIC EnigmaABC)