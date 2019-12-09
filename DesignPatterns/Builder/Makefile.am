# Automake created by Mani Kumar

# build lib
lib_LTLIBRARIES = libBuilder.la
libBuilder_la_CPPFLAGS = -I$(srcdir)/inc
libBuilder_la_LDFLAGS = -version-info 1:0:0
# lib headers
libBuilder_la_SOURCES = \
  inc/carbuilder.h
# lib sources
libBuilder_la_SOURCES += \
  src/carbuilder.cpp

# build bins
bin_PROGRAMS = Builder

Builder_SOURCES = main.cpp
Builder_CPPFLAGS = -I$(srcdir)/inc
Builder_LDADD = libBuilder.la

# build test-bin
check_PROGRAMS = test_Builder

test_Builder_SOURCES = test/test_carbuilder.cpp # test/test_main.cpp
test_Builder_LDADD = libBuilder.la

test_Builder_CPPFLAGS = -I$(srcdir)/inc
test_Builder_CPPFLAGS += -isystem $(top_srcdir)/ext/lib/googletest/googletest/include/ $(GTEST_CPPFLAGS)
#test_Builder_CPPFLAGS += -isystem $(top_srcdir)/ext/lib/googletest/googlemock/include/

test_Builder_CXXFLAGS = $(GTEST_CXXFLAGS)
test_Builder_LDFLAGS = \
  $(GTEST_LDFLAGS) \
  $(GTEST_LIBS) \
  $(top_builddir)/ext/lib/googletest/googletest/libgtest_main.la \
  $(top_builddir)/ext/lib/googletest/googletest/libgtest.la

TESTS = test_Builder
