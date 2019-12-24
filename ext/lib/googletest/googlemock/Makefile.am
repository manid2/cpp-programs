# list gmock files for distribution
GMOCK_SRC = \
  include/gmock/gmock-actions.h \
  include/gmock/gmock-cardinalities.h \
  include/gmock/gmock-function-mocker.h \
  include/gmock/gmock-generated-actions.h \
  include/gmock/gmock-generated-function-mockers.h \
  include/gmock/gmock-generated-matchers.h \
  include/gmock/gmock.h \
  include/gmock/gmock-matchers.h \
  include/gmock/gmock-more-actions.h \
  include/gmock/gmock-more-matchers.h \
  include/gmock/gmock-nice-strict.h \
  include/gmock/gmock-spec-builders.h \
  include/gmock/internal/custom/gmock-generated-actions.h \
  include/gmock/internal/custom/gmock-matchers.h \
  include/gmock/internal/custom/gmock-port.h \
  include/gmock/internal/gmock-internal-utils.h \
  include/gmock/internal/gmock-port.h \
  include/gmock/internal/gmock-pp.h

GMOCK_SRC += \
  src/gmock-all.cc \
  src/gmock-cardinalities.cc \
  src/gmock.cc \
  src/gmock-internal-utils.cc \
  src/gmock_main.cc \
  src/gmock-matchers.cc \
  src/gmock-spec-builders.cc

EXTRA_DIST = $(GMOCK_SRC)

# We define the global AM_CPPFLAGS as everything we compile includes from these
# directories.
AM_CPPFLAGS = \
  -isystem $(srcdir)/include \
  -isystem $(srcdir)/../googletest/include \
  $(GTEST_CPPFLAGS)
AM_CXXFLAGS = $(GTEST_CXXFLAGS)
AM_LDFLAGS = $(GTEST_LDFLAGS)
LDADD = $(GTEST_LIBS)

# Build rules for libraries.
noinst_LTLIBRARIES = libgmock.la libgmock_main.la

libgmock_la_SOURCES = src/gmock-all.cc

libgmock_main_la_SOURCES = src/gmock_main.cc
libgmock_main_la_LIBADD = libgmock.la
