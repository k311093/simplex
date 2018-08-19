cmake_minimum_required(VERSION 3.1)

project("runtime" C)

set(RUNTIME_SRC_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
    CACHE INTERNAL "RUNTIME_SRC_DIR")
set(RUNTIME_BIN_DIR
    ${CMAKE_CURRENT_BINARY_DIR}
    CACHE INTERNAL "RUNTIME_BIN_DIR")
set(RUNTIME_INC_DIR
    ${RUNTIME_SRC_DIR}/include
    CACHE INTERNAL "RUNTIME_INC_DIR")

include_directories(${RUNTIME_INC_DIR})

if(${CMAKE_C_COMPILER_ID} STREQUAL MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /O2 /W4")
    set(PLATFORM_LIBS )
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -Wextra")
    set(PLATFORM_LIBS pthread)
endif()

if(PLATFORM_WINDOWS)
    set(PLATFORM_SRC
        thread_win.c
        sysinfo_win.c
        page_win.c)
elseif(PLATFORM_MACOS)
    set(PLATFORM_SRC
        thread_mac.c
        sysinfo_mac.c
        page_mac.c)
elseif(PLATFORM_LINUX)
    set(PLATFORM_SRC
        thread_linux.c
        sysinfo_linux.c
        page_linux.c)
endif()

set(RUNTIME_SRC
    ${PLATFORM_SRC}
    atomic.c
    cell.c
    murmur3.c
    queue.c
    rbtree.c)

add_library(runtime ${RUNTIME_SRC})
target_link_libraries(runtime ${PLATFORM_LIBS})

add_subdirectory(external)
add_subdirectory(tests)
