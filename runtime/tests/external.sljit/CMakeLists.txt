cmake_minimum_required(VERSION 3.1)

include_directories(${SLJIT_INC_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${TEST_BINARY_DIR}/runtime.external.sljit)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
    ${TEST_BINARY_DIR}/runtime.external.sljit)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
    ${TEST_BINARY_DIR}/runtime.external.sljit)

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4146 /wd4244 /wd4127")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4245 /wd4308 /wd4389")
endif()

if(CMAKE_COMPILER_IS_GCC OR CMAKE_COMPILER_IS_CLANG OR MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-sign-compare")
endif()

add_definitions(-DSLJIT_DEBUG=0)
add_definitions(-DSLJIT_VERBOSE=0)
add_definitions(-DSLJIT_CONFIG_AUTO=1)

add_executable(sljit_test sljitMain.c sljitTest.c)
target_link_libraries(sljit_test sljit)
add_test(sljit ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sljit_test)

add_executable(sljit_regex_test regexJIT.c regexMain.c)
target_link_libraries(sljit_regex_test sljit)
add_test(sljit_regex ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sljit_regex_test)
