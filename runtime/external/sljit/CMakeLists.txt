cmake_minimum_required(VERSION 3.1)

project("sljit" C)

set(SLJIT_VER sljit-0.93)

set(SLJIT_SRC_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/${SLJIT_VER}/sljit_src
    CACHE INTERNAL "SLJIT_SRC_DIR")
set(SLJIT_BIN_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/${SLJIT_VER}
    CACHE INTERNAL "SLJIT_BIN_DIR")
set(SLJIT_INC_DIR
    ${SLJIT_SRC_DIR}
    CACHE INTERNAL "SLJIT_INC_DIR")

set(SLJIT_SRC
    ${SLJIT_SRC_DIR}/sljitLir.c
)

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4146 /wd4244 /wd4127")
endif()

if(CMAKE_COMPILER_IS_GCC OR CMAKE_COMPILER_IS_CLANG OR MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-sign-compare")
endif()

add_definitions(-DSLJIT_DEBUG=0)
add_definitions(-DSLJIT_VERBOSE=0)
add_definitions(-DSLJIT_CONFIG_AUTO=1)

add_library(sljit ${SLJIT_SRC})
