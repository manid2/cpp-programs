cmake_minimum_required(VERSION 2.8)

get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/)
file(GLOB module_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(SRCS main.cpp ${module_srcs})

add_executable(${MODULE_NAME} ${SRCS})

# includes gtest
enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB module_test_srcs ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
set(TEST_EXE "test_${MODULE_NAME}")
add_executable(${TEST_EXE} ${module_test_srcs} ${module_srcs})
target_link_libraries(${TEST_EXE} gmock_main gtest_main)
add_test(NAME ${TEST_EXE} COMMAND ${MODULE_NAME})
