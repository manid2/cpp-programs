#####################################################################
# CppCodeExamples
#####################################################################

# Set minimum cmake version
cmake_minimum_required(VERSION 3.15)

# Provide project info
# TODO: Update HOMEPAGE_URL
project(
    "CppCodeExamples"
    VERSION 1.0.0
    LANGUAGES C CXX
    DESCRIPTION "C++ code examples for common reusable problems."
)

# Set minimum C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # disable the fallback behaviour
set(CMAKE_CXX_EXTENSIONS OFF) # use -std=c++11 and not -std=gnu++11

# Add sub directories to the project
add_subdirectory(CodeCoverage)
add_subdirectory(StructuredData)
add_subdirectory(UnitTesting)

# Add external libraries
# TODO: make `make test` rule optional, i.e. use BUILD_TESTING option
enable_testing()
add_subdirectory(ext/lib/googletest)

# TODO: Add optional builds: doxygen, GNOME/libxml2 or GNOME/libxmlplusplus,
#   nlohmann/json.

# Use the below cmake command to generate the cmake eclipse project
# cmake ../cpp-code-examples \
#     -G"Eclipse CDT4 - Unix Makefiles" \
#     -DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE \
#     -DCMAKE_BUILD_TYPE=Debug
