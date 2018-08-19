cmake_minimum_required(VERSION 3.1)

project("simplex" C)

set(SIMPLEX_VERSION_MAJOR "1")
set(SIMPLEX_VERSION_MINOR "0")

string(CONCAT
    SIMPLEX_VERSION
    "${SIMPLEX_VERSION_MAJOR}" "." "${SIMPLEX_VERSION_MINOR}")

include(TestBigEndian)

option(USE_OPENCL   "Use OpenCL"   OFF)
option(USE_THREAD   "Use Thread"   ON)
option(USE_JIT      "Use JIT"      ON)

enable_testing()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

set(TEST_BINARY_DIR ${CMAKE_BINARY_DIR}/tests)

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /wd4819")
endif()

if(USE_OPENCL)
    find_package(OpenCL 1.2 REQUIRED)
endif()

if(WIN32)
    set(PLATFORM_WINDOWS True)
elseif(APPLE)
    set(PLATFORM_MACOS True)
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_LINUX True)
else()
    message(FATAL_ERROR "Cannot detect platform")
endif()

TEST_BIG_ENDIAN(IS_BIG_ENDIAN)

string(REGEX MATCH "Clang" CMAKE_COMPILER_IS_CLANG "${CMAKE_C_COMPILER_ID}")
string(REGEX MATCH "GNU"   CMAKE_COMPILER_IS_GCC   "${CMAKE_C_COMPILER_ID}")

if(CMAKE_COMPILER_MATCH_GCC)
    set(CMAKE_COMPILER_IS_GCC True)
else()
    set(CMAKE_COMPILER_IS_GCC False)
endif()

if(IS_BIG_ENDIAN)
    set(CMAKE_BIG_ENDIAN 1)
else()
    set(CMAKE_BIG_ENDIAN 0)
endif()

if(USE_OPENCL)
    set(CMAKE_USE_OPENCL 1)
else()
    set(CMAKE_USE_OPENCL 0)
endif()

if(USE_THREAD)
    set(CMAKE_USE_THREAD 1)
else()
    set(CMAKE_USE_THREAD 0)
endif()

if(USE_JIT)
    set(CMAKE_USE_JIT 1)
else()
    set(CMAKE_USE_JIT 0)
endif()

if(PLATFORM_WINDOWS)
    set(CMAKE_PLATFORM_WINDOWS 1)
else()
    set(CMAKE_PLATFORM_WINDOWS 0)
endif()

if(PLATFORM_MACOS)
    set(CMAKE_PLATFORM_MACOS 1)
else()
    set(CMAKE_PLATFORM_MACOS 0)
endif()

if(PLATFORM_LINUX)
    set(CMAKE_PLATFORM_LINUX 1)
else()
    set(CMAKE_PLATFORM_LINUX 0)
endif()

if(MSVC)
    set(CMAKE_COMPILER_MSVC 1)
else()
    set(CMAKE_COMPILER_MSVC 0)
endif()

if(MINGW)
    set(CMAKE_COMPILER_MINGW 1)
else()
    set(CMAKE_COMPILER_MINGW 0)
endif()

if(CMAKE_COMPILER_IS_CLANG)
    set(CMAKE_COMPILER_CLANG 1)
else()
    set(CMAKE_COMPILER_CLANG 0)
endif()

if(CMAKE_COMPILER_IS_GCC)
    set(CMAKE_COMPILER_GCC 1)
else()
    set(CMAKE_COMPILER_GCC 0)
endif()

configure_file(
    ${CMAKE_SOURCE_DIR}/config.h.in
    ${CMAKE_BINARY_DIR}/include/simplex/config.h
    @ONLY)

include_directories(${CMAKE_BINARY_DIR}/include)

if(USE_OPENCL)
    include_directories(${OpenCL_INCLUDE_DIRS})
    link_directories(${OpenCL_LIBRARY})
endif()

add_subdirectory(external)
add_subdirectory(runtime)
#add_subdirectory(library)
