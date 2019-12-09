# Automake created by Mani Kumar

AM_CPPFLAGS = -isystem $(top_srcdir)/ext/lib/googletest/googletest/include/
#AM_CPPFLAGS += -isystem $(top_srcdir)/ext/lib/googletest/googlemock/include/
AM_CPPFLAGS += -I$(srcdir)/inc $(GTEST_CPPFLAGS)

AM_CXXFLAGS = $(GTEST_CXXFLAGS)
AM_LDFLAGS = $(GTEST_LDFLAGS) $(GTEST_LIBS) \
       $(top_builddir)/ext/lib/googletest/googletest/libgtest_main.la \
       $(top_builddir)/ext/lib/googletest/googletest/libgtest.la

# build lib
lib_LTLIBRARIES = libBuilder.la
libBuilder_la_LDFLAGS = -version-info 1:0:0
# lib headers
libBuilder_la_SOURCES = \
  inc/carbuilder.h \
  inc/cburgerbuilder.h \
  inc/cxmlbuilder.h \
  inc/cxmldombuilder.h
# lib sources
libBuilder_la_SOURCES += \
  src/carbuilder.cpp \
  src/cburgerbuilder.cpp \
  src/cxmlbuilder.cpp \
  src/cxmldombuilder.cpp

# build bins
bin_PROGRAMS = Builder

Builder_SOURCES = main.cpp
Builder_LDADD = libBuilder.la


# build test-bin
#test_Lcc_SOURCES = test/test_stringproblems.cpp
TESTS =
check_PROGRAMS =

TESTS += test_Builder
check_PROGRAMS += test_Builder
test_Builder_SOURCES = test/test_carbuilder.cpp # test/test_main.cpp
test_Builder_LDADD = libBuilder.la
