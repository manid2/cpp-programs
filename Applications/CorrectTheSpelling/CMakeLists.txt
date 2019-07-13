cmake_minimum_required(VERSION 3.0)

get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/)
file(GLOB module_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(SRCS main.cpp ${module_srcs})

add_executable(${MODULE_NAME} ${SRCS})
target_link_libraries(${MODULE_NAME} aspell)

# includes gtest
enable_testing()
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB module_test_srcs ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
set(TEST_EXE "test_${MODULE_NAME}")
add_executable(${TEST_EXE} ${module_test_srcs} ${module_srcs})
target_link_libraries(${TEST_EXE} aspell gmock_main gtest_main)
add_test(NAME ${TEST_EXE} COMMAND ${MODULE_NAME})

#-- target for doc
# build docs by default
option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/${MODULE_NAME}.doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
    
    # note the option ALL which allows to build the docs together with the application
    add_custom_target( ${MODULE_NAME}-doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
