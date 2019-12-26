# Automake created by Mani Kumar

#==============================================================================
# src code build variables
#==============================================================================
# external libs code path
EXT_PATH = $(top_srcdir)/ext
EXT_LIB_PATH = $(EXT_PATH)/lib
EXT_LIB_GOOGLETEST_PATH = $(EXT_LIB_PATH)/googletest

# build libs
lib_LTLIBRARIES = libComposite.la

#== libComposite.la
libComposite_la_CPPFLAGS = \
  -I$(srcdir)/inc
# lib headers
libComposite_la_SOURCES = \
  inc/cgraphic.h
# lib sources
libComposite_la_SOURCES += \
  src/cgraphic.cpp
# lib deps flags
libComposite_la_LDFLAGS = \
  -version-info 1:0:0
# lib deps list
#libComposite_la_LIBADD = \
#  $(top_builddir)/ext/lib/yajl/libyajl.la

# build bins
bin_PROGRAMS = Composite

#== Composite
Composite_SOURCES = main.cpp
Composite_CPPFLAGS = \
  $(libComposite_la_CPPFLAGS)
Composite_LDADD = libComposite.la

#==============================================================================
# test code build variables
#==============================================================================
# build test-bin
EXTRA_DIST = test/test_precomp.h
check_PROGRAMS = test_Composite

#== test_Composite
test_Composite_SOURCES = test/test_cgraphic.cpp

test_Composite_CPPFLAGS = \
  $(libComposite_la_CPPFLAGS) \
  -isystem $(EXT_LIB_GOOGLETEST_PATH)/googlemock/include/ \
  -isystem $(EXT_LIB_GOOGLETEST_PATH)/googletest/include/ \
  $(GTEST_CPPFLAGS)

test_Composite_CXXFLAGS = $(GTEST_CXXFLAGS)
test_Composite_LDFLAGS = \
  $(GTEST_LDFLAGS) \
  $(GTEST_LIBS) \
  -no-install

test_Composite_LDADD = \
  libComposite.la \
  $(top_builddir)/ext/lib/googletest/googlemock/libgmock_main.la \
  $(top_builddir)/ext/lib/googletest/googlemock/libgmock.la \
  $(top_builddir)/ext/lib/googletest/googletest/libgtest.la

TESTS = test_Composite
