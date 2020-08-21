# Learn GCov tool, sample code targets

#-- learn_gcov_by_example
# include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/)
# set source files
set(LGF_MODULE_NAME "learn_gcov_by_example")
set(LGF_SRCS
    main.cc
    src/learn_gcov_func.cc
    inc/learn_gcov_func.hh
)
# add executable
add_executable(${LGF_MODULE_NAME} ${LGF_SRCS})
