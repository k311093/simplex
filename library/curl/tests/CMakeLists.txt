cmake_minimum_required(VERSION 3.1)

include_directories(${CURL_INC_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${TEST_BINARY_DIR}/library.curl)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
    ${TEST_BINARY_DIR}/library.curl)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
    ${TEST_BINARY_DIR}/library.curl)

add_definitions(-DCURL_STATICLIB)

add_executable(curl_test curl_test.c)

target_link_libraries(curl_test libcurl)
