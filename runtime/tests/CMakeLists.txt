cmake_minimum_required(VERSION 3.1)

project("runtime_tests" C)

include_directories(${UNITY_INC_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${TEST_BINARY_DIR}/runtime)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
    ${TEST_BINARY_DIR}/runtime)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
    ${TEST_BINARY_DIR}/runtime)

add_executable(murmur3_test murmur3_test.c)
target_link_libraries(murmur3_test runtime unity)
add_test(murmur3 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/murmur3_test)

add_executable(thread_test thread_test.c)
target_link_libraries(thread_test runtime unity)
add_test(thread_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thread_test)

add_executable(atomic_test atomic_test.c)
target_link_libraries(atomic_test runtime unity)
add_test(atomic_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/atomic_test)

add_executable(sysinfo_test sysinfo_test.c)
target_link_libraries(sysinfo_test runtime unity)
add_test(sysinfo_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sysinfo_test)

add_executable(page_test page_test.c)
target_link_libraries(page_test runtime unity)
add_test(page_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/page_test)

add_executable(mutex_test mutex_test.c)
target_link_libraries(mutex_test runtime unity)
add_test(mutex_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mutex_test)

add_executable(queue_test queue_test.c)
target_link_libraries(queue_test runtime unity)
add_test(queue_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/queue_test)

add_executable(cell_test cell_test.c)
target_link_libraries(cell_test runtime unity)
add_test(cell_test ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cell_test)

if(USE_JIT)
    add_subdirectory(external.sljit)
endif()
