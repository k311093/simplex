cmake_minimum_required(VERSION 3.1)

project("primitive" C)

set(PRIMITIVE_SRC_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE INTERNAL "PRIMITIVE_SRC_DIR")
set(PRIMITIVE_BIN_DIR
    ${CMAKE_CURRENT_BINARY_DIR}
    CACHE INTERNAL "PRIMITIVE_BIN_DIR")
set(PRIMITIVE_INC_DIR
    ${PRIMITIVE_SRC_DIR}
    CACHE INTERNAL "PRIMITIVE_INC_DIR")

if(${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2 /W4")
    set(PLATFORM_LIBS )
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -Wextra")
    set(PLATFORM_LIBS m)
endif()

include_directories(${RUNTIME_INC_DIR})

if(PLATFORM_WINDOWS)
    set(PLATFORM_SRC
        device_rand_win.c)
elseif(PLATFORM_MACOS)
    set(PLATFORM_SRC
        device_rand_mac.c)
elseif(PLATFORM_LINUX)
    set(PLATFORM_SRC
        device_rand_linux.c)
endif()

set(PRIMITIVE_SRC
    ${PLATFORM_SRC}
    mt19937.c)

add_library(primitive ${PRIMITIVE_SRC})
target_link_libraries(primitive ${PLATFORM_LIBS} runtime)

add_subdirectory(tests)
