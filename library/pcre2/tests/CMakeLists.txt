cmake_minimum_required(VERSION 3.1)

include_directories(${PCRE2_SRC_DIR})
include_directories(${PCRE2_BIN_DIR})
include_directories(${PCRE2_INC_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${TEST_BINARY_DIR}/library.pcre2)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
    ${TEST_BINARY_DIR}/library.pcre2)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
    ${TEST_BINARY_DIR}/library.pcre2)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4090")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4005")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4267")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4018")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4146")
endif(MSVC)

add_definitions(-DHAVE_CONFIG_H)
add_definitions(-DPCRE2_STATIC)
add_definitions(-DPCRE2_CODE_UNIT_WIDTH=8)

add_executable(pcre2_test pcre2test.c)
target_link_libraries(pcre2_test pcre2-8 pcre2-posix)

add_executable(pcre2_demo pcre2demo.c)
target_link_libraries(pcre2_demo pcre2-8 pcre2-posix)

add_executable(pcre2_grep pcre2grep.c)
target_link_libraries(pcre2_grep pcre2-8 pcre2-posix)

if(USE_JIT)
    add_executable(pcre2_jit_test pcre2_jit_test.c)
    target_link_libraries(pcre2_jit_test pcre2-8 pcre2-posix)
    add_test(pcre2_jit ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/pcre2_jit_test)
endif()
