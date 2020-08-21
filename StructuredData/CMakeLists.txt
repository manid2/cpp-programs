# Structred data parse/write examples

#-- pidf_parser_writer target
# set target variables
set(PIDF_PARSER_WRITER "pidf_parser_writer")
set(PIDF_PARSER_WRITER_PVT_LIB
    "lib_${PIDF_PARSER_WRITER}")
#set(PIDF_PARSER_WRITER_EXE
#    "exe_${PIDF_PARSER_WRITER}")
# set header files
set(PIDF_PARSER_WRITER_HDRS
    inc/ParseWritePidfData.hh
)
# set source files
set(PIDF_PARSER_WRITER_SRCS
    src/ParseWritePidfData.cc
)
# build static lib
add_library(${PIDF_PARSER_WRITER_PVT_LIB} STATIC
    ${PIDF_PARSER_WRITER_SRCS}
    ${PIDF_PARSER_WRITER_HDRS}
)
# target include directories
target_include_directories(${PIDF_PARSER_WRITER_PVT_LIB} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
)
# find external dependencies
find_package(LibXml2 REQUIRED)
# TODO: build nothing if required dependencies are not found
# include external libs
target_include_directories(${PIDF_PARSER_WRITER_PVT_LIB} PUBLIC
    ${LIBXML2_INCLUDE_DIR}
)
# include external libs
target_link_libraries(${PIDF_PARSER_WRITER_PVT_LIB} PUBLIC
    ${LIBXML2_LIBRARIES}
)
# build test binary
# TODO: add test target
