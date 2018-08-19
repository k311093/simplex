cmake_minimum_required(VERSION 3.1)

project("zlib" C)

set(ZLIB_VER zlib-1.2.11)

set(ZLIB_SRC_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/${ZLIB_VER}
    CACHE INTERNAL "ZLIB_SRC_DIR")
set(ZLIB_BIN_DIR
    ${CMAKE_CURRENT_BINARY_DIR}/${ZLIB_VER}
    CACHE INTERNAL "ZLIB_BIN_DIR")
set(ZLIB_INC_DIR
    ${ZLIB_SRC_DIR} ${ZLIB_BIN_DIR}
    CACHE INTERNAL "ZLIB_INC_DIR")

if(MSVC)
    add_definitions(/D_CRT_SECURE_NO_DEPRECATE)
    add_definitions(/D_CRT_NONSTDC_NO_DEPRECATE)
    include_directories(${ZLIB_SRC_DIR})
endif()

configure_file(${ZLIB_SRC_DIR}/zconf.h.cmakein
               ${ZLIB_BIN_DIR}/zconf.h
               @ONLY)

include_directories(${ZLIB_SRC_DIR} ${ZLIB_BIN_DIR})

#============================================================================
# zlib
#============================================================================

set(ZLIB_PUBLIC_HDRS
    ${ZLIB_BIN_DIR}/zconf.h
    ${ZLIB_SRC_DIR}/zlib.h
)

set(ZLIB_PRIVATE_HDRS
    ${ZLIB_SRC_DIR}/crc32.h
    ${ZLIB_SRC_DIR}/deflate.h
    ${ZLIB_SRC_DIR}/gzguts.h
    ${ZLIB_SRC_DIR}/inffast.h
    ${ZLIB_SRC_DIR}/inffixed.h
    ${ZLIB_SRC_DIR}/inflate.h
    ${ZLIB_SRC_DIR}/inftrees.h
    ${ZLIB_SRC_DIR}/trees.h
    ${ZLIB_SRC_DIR}/zutil.h
)

set(ZLIB_SRCS
    ${ZLIB_SRC_DIR}/adler32.c
    ${ZLIB_SRC_DIR}/compress.c
    ${ZLIB_SRC_DIR}/crc32.c
    ${ZLIB_SRC_DIR}/deflate.c
    ${ZLIB_SRC_DIR}/gzclose.c
    ${ZLIB_SRC_DIR}/gzlib.c
    ${ZLIB_SRC_DIR}/gzread.c
    ${ZLIB_SRC_DIR}/gzwrite.c
    ${ZLIB_SRC_DIR}/inflate.c
    ${ZLIB_SRC_DIR}/infback.c
    ${ZLIB_SRC_DIR}/inftrees.c
    ${ZLIB_SRC_DIR}/inffast.c
    ${ZLIB_SRC_DIR}/trees.c
    ${ZLIB_SRC_DIR}/uncompr.c
    ${ZLIB_SRC_DIR}/zutil.c
)

# parse the full version number from zlib.h and include in ZLIB_FULL_VERSION
file(READ ${ZLIB_SRC_DIR}/zlib.h _zlib_h_contents)
string(REGEX REPLACE ".*#define[ \t]+ZLIB_VERSION[ \t]+\"([-0-9A-Za-z.]+)\".*"
    "\\1" ZLIB_FULL_VERSION ${_zlib_h_contents})

add_library(zlib
    ${ZLIB_SRCS} ${ZLIB_ASMS} ${ZLIB_DLL_SRCS}
    ${ZLIB_PUBLIC_HDRS} ${ZLIB_PRIVATE_HDRS}
)

add_subdirectory(tests)
