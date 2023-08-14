#####################################################################
# Target level CMakeLists.txt file
#####################################################################

#-- set module variables
get_filename_component(module_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(module_include ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
file(GLOB module_headers ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h)
file(GLOB module_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

#-- target for lib build
string(TOLOWER ${module_name} module_lib_name)
set(module_lib_name "${module_lib_name}_lib")
add_library(${module_lib_name} STATIC ${module_sources} ${module_headers})
target_include_directories(${module_lib_name} PRIVATE ${module_include})

#-- target for exe build
set(exe_srcs main.cpp)
add_executable(${module_name} ${exe_srcs})
target_include_directories(${module_name} PRIVATE ${module_include})
target_link_libraries(${module_name} PRIVATE ${module_lib_name})

#-- target for test build
# TODO make tests conditional
#file(GLOB module_tests ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
#enable_testing()
#set(module_tests_name "test_${module_name}")
#add_executable(${module_tests_name} ${module_tests})
#target_include_directories(${module_tests_name} PRIVATE ${module_include})
#target_link_libraries(${module_tests_name} PRIVATE ${module_lib_name}
#  aspell gmock_main gtest_main)
#add_test(NAME ${module_tests_name} COMMAND ${module_name})
