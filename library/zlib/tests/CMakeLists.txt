cmake_minimum_required(VERSION 3.1)

include_directories(${ZLIB_INC_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${TEST_BINARY_DIR}/library.zlib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
    ${TEST_BINARY_DIR}/library.zlib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
    ${TEST_BINARY_DIR}/library.zlib)

if(MSVC)
    add_definitions(/D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(/D_CRT_NONSTDC_NO_DEPRECATE)
    add_definitions(/wd4131)
endif()

add_executable(zlib_basic zlib_basic.c)
target_link_libraries(zlib_basic zlib)
add_test(zlib_basic ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zlib_basic)

add_executable(zlib_infcover zlib_infcover.c)
target_link_libraries(zlib_infcover zlib)
add_test(zlib_infcover ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/zlib_infcover)

add_executable(zlib_minigzip zlib_minigzip.c)
target_link_libraries(zlib_minigzip zlib)
