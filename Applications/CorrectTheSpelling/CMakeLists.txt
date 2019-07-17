cmake_minimum_required(VERSION 3.0)

#-- set module variables
get_filename_component(module_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(module_include ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
file(GLOB module_headers ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB module_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB module_tests ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

#-- target for lib build
string(TOLOWER ${module_name} module_lib_name)
add_library(${module_lib_name} STATIC ${module_sources} ${module_headers})
target_include_directories(${module_lib_name} PRIVATE ${module_include})

#-- target for exe build
set(exe_srcs main.cpp)
add_executable(${module_name} ${exe_srcs})
target_include_directories(${module_name} PRIVATE ${module_include})
target_link_libraries(${module_name} PRIVATE ${module_lib_name} aspell)

#-- target for test build
enable_testing()
set(module_tests_name "test_${module_name}")
add_executable(${module_tests_name} ${module_tests})
target_include_directories(${module_tests_name} PRIVATE ${module_include})
target_link_libraries(${module_tests_name} PRIVATE ${module_lib_name} 
  aspell gmock_main gtest_main)
add_test(NAME ${module_tests_name} COMMAND ${module_name})

#-- target for doc build
option(BUILD_DOC "Build documentation" ON)
find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/${module_name}.doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")
    
    # note the option ALL which allows to build the docs together with the application
    add_custom_target(${module_name}-doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
