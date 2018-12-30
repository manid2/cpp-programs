cmake_minimum_required(VERSION 3.0)

#get_filename_component(MODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

message( STATUS "CMAKE_CURRENT_SOURCE_DIR:         " ${CMAKE_CURRENT_SOURCE_DIR} )
LIST_SUBDIRS(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

message( STATUS "========== Adding modules to build ==========" )
foreach(subdir ${SUBDIRS})
  add_subdirectory(${subdir})
  message( STATUS "Added subdir: " ${subdir} )
endforeach()
message( STATUS "========== All modules are added ==========" )
