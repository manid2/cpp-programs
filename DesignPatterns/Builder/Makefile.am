# Automake created by Mani Kumar

#==============================================================================
# src code build variables
#==============================================================================
# external libs code path
EXT_PATH = $(top_srcdir)/ext
EXT_LIB_PATH = $(EXT_PATH)/lib
EXT_LIB_GOOGLETEST_PATH = $(EXT_LIB_PATH)/googletest

# build libs
lib_LTLIBRARIES = libBuilder.la

#== libBuilder.la
libBuilder_la_CPPFLAGS = \
  -I$(srcdir)/inc
# lib headers
libBuilder_la_SOURCES = \
  inc/carbuilder.h
# lib sources
libBuilder_la_SOURCES += \
  src/carbuilder.cpp
# lib deps flags
libBuilder_la_LDFLAGS = \
  -version-info 1:0:0
# lib deps list
#libBuilder_la_LIBADD = \
#  $(top_builddir)/ext/lib/yajl/libyajl.la

# build bins
bin_PROGRAMS = Builder

#== Builder
Builder_SOURCES = main.cpp
Builder_CPPFLAGS = -I$(srcdir)/inc
Builder_LDADD = libBuilder.la

#==============================================================================
# test code build variables
#==============================================================================
# build test-bin
EXTRA_DIST = test/test_precomp.h
check_PROGRAMS = test_Builder

#== test_Builder
test_Builder_SOURCES = test/test_carbuilder.cpp

test_Builder_CPPFLAGS = \
  $(libBuilder_la_CPPFLAGS) \
  -isystem $(EXT_LIB_GOOGLETEST_PATH)/googlemock/include/ \
  -isystem $(EXT_LIB_GOOGLETEST_PATH)/googletest/include/ \
  $(GTEST_CPPFLAGS)

test_Builder_CXXFLAGS = $(GTEST_CXXFLAGS)
test_Builder_LDFLAGS = \
  $(GTEST_LDFLAGS) \
  $(GTEST_LIBS) \
  -no-install

test_Builder_LDADD = \
  libBuilder.la \
  $(top_builddir)/ext/lib/googletest/googlemock/libgmock_main.la \
  $(top_builddir)/ext/lib/googletest/googlemock/libgmock.la \
  $(top_builddir)/ext/lib/googletest/googletest/libgtest.la

TESTS = test_Builder
