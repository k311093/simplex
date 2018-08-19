cmake_minimum_required(VERSION 3.1)

project("primitive_tests" C)

include_directories(${UNITY_INC_DIR})
include_directories(${PRIMITIVE_INC_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${TEST_BINARY_DIR}/library.primitive)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
    ${TEST_BINARY_DIR}/library.primitive)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
    ${TEST_BINARY_DIR}/library.primitive)

add_executable(mt19937_test mt19937_test.c)
target_link_libraries(mt19937_test primitive unity)
add_test(mt19937_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mt19937_test)
