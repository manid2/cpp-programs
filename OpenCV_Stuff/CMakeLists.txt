cmake_minimum_required(VERSION 2.8)

get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/)
file(GLOB module_srcs ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(SRCS main.cpp ${module_srcs})

# debug macros
#add_definitions(-DWITH_DUMMY_PAGE_DATA)
string(TOLOWER ${MODULE_NAME} MODULE_NAME)

find_package( OpenCV REQUIRED )
add_executable(${MODULE_NAME} ${SRCS})
target_link_libraries(${MODULE_NAME}  ${OpenCV_LIBS})
