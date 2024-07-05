cmake_minimum_required(VERSION 3.15)

project(enigma VERSION 0.1.0
    DESCRIPTION "Enigma machine simulator"
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif()

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

if(ENABLE_COVERAGE)
    # add compiler flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0 -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")

    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E make_directory coverage
        COMMAND lcov --capture --directory . --output-file coverage/coverage.info
        COMMAND lcov --list coverage/coverage.info
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()

# ################### Backend ##################
add_subdirectory(src)
add_executable(enigma src/main.c)
target_link_libraries(enigma enigma_lib)

# ##############################################

# ################### TESTS ####################
add_subdirectory(tests)
add_executable(enigma_test tests/main.c)

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

# ##############################################
