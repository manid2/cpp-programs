cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 11)

project(ProgramsForFun)
#add_subdirectory(Builder)
#add_subdirectory(Composite)

# Adding sub dirs automatically
# macro(<name> [arg1 [arg2 [arg3 ...]]])
#  COMMAND1(ARGS ...)
#  COMMAND2(ARGS ...)
#  ...
# endmacro(<name>)
macro(LIST_SUBDIRS result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/[^.]*)
  message( STATUS "curdir: " ${curdir} )
  message( STATUS "========== Finding modules to build ==========" )
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND dirlist ${child})
      message( STATUS "Found subdir: " ${child} )
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()


message( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )
LIST_SUBDIRS(SUBDIRS ${CMAKE_SOURCE_DIR})

message( STATUS "========== Adding modules to build ==========" )
foreach(subdir ${SUBDIRS})
  add_subdirectory(${subdir})
  message( STATUS "Added subdir: " ${subdir} )
endforeach()
message( STATUS "========== All modules are added ==========" )

#####################################################################
# Add gtest and gmock
# for detailed instructions read the article from:
# https://crascit.com/2015/07/25/cmake-gtest/
# The below code is borrowed from there.
#
#####################################################################
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

# Use the below cmake command to generate the cmake eclipse project
# cmake ../ProgramsForFun \
#       -G"Eclipse CDT4 - Unix Makefiles" \
#       -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
#       -DCMAKE_BUILD_TYPE=Debug \
#       -DCMAKE_CXX_FLAGS="-std=c++11" \
#       -DCMAKE_CXX_COMPILER_ARG1=-std=c++11