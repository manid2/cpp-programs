# gtest & gmock techniques, sample code targets

#-- gtest_gmock_consumer_producer
# set target variables
set(GTEST_GMOCK_CONSUMER_PRODUCER "gtest_gmock_consumer_producer")
set(GTEST_GMOCK_CONSUMER_PRODUCER_PVT_LIB
    "lib_${GTEST_GMOCK_CONSUMER_PRODUCER}")
#set(GTEST_GMOCK_CONSUMER_PRODUCER_EXE
#    "exe_${GTEST_GMOCK_CONSUMER_PRODUCER}")
# set header files
set(GTEST_GMOCK_CONSUMER_PRODUCER_HDRS
    inc/consumer.hh
    inc/producer.hh
)
# set source files
set(GTEST_GMOCK_CONSUMER_PRODUCER_SRCS
    src/consumer.cc
    src/producer.cc
)
# build static lib
add_library(${GTEST_GMOCK_CONSUMER_PRODUCER_PVT_LIB} STATIC
    ${GTEST_GMOCK_CONSUMER_PRODUCER_SRCS}
    ${GTEST_GMOCK_CONSUMER_PRODUCER_HDRS}
)
# target include directories
target_include_directories(${GTEST_GMOCK_CONSUMER_PRODUCER_PVT_LIB} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc/>
)
# build test binary
# set source files
set(GTEST_GMOCK_CONSUMER_PRODUCER_TEST_SRCS
    test/test_producer.cc
)
set(GTEST_GMOCK_CONSUMER_PRODUCER_TEST_EXE
    "test_${GTEST_GMOCK_CONSUMER_PRODUCER}")
# add test target
add_executable(${GTEST_GMOCK_CONSUMER_PRODUCER_TEST_EXE}
    ${GTEST_GMOCK_CONSUMER_PRODUCER_TEST_SRCS}
)
# link test binary to dependencies
target_link_libraries(${GTEST_GMOCK_CONSUMER_PRODUCER_TEST_EXE}
    ${GTEST_GMOCK_CONSUMER_PRODUCER_PVT_LIB}
    gmock_main
    gmock
    gtest
)
# add test to make rule 'make test'
# FIXME: `make test` rule is not created
add_test(${GTEST_GMOCK_CONSUMER_PRODUCER_TEST_EXE}
    ${GTEST_GMOCK_CONSUMER_PRODUCER_TEST_EXE}
)
