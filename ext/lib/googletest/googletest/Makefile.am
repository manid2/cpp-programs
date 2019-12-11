# list gtest files for distribution
GTEST_SRC = \
  src/gtest-internal-inl.h \
  src/gtest.cc \
  src/gtest-matchers.cc \
  src/gtest-all.cc \
  src/gtest-test-part.cc \
  src/gtest-port.cc \
  src/gtest-filepath.cc \
  src/gtest_main.cc \
  src/gtest-printers.cc \
  src/gtest-typed-test.cc \
  src/gtest-death-test.cc

GTEST_SRC += \
  include/gtest/gtest-spi.h \
  include/gtest/gtest.h \
  include/gtest/gtest_pred_impl.h \
  include/gtest/gtest-typed-test.h \
  include/gtest/gtest-printers.h \
  include/gtest/internal/gtest-port-arch.h \
  include/gtest/internal/gtest-port.h \
  include/gtest/internal/gtest-filepath.h \
  include/gtest/internal/gtest-type-util.h \
  include/gtest/internal/gtest-internal.h \
  include/gtest/internal/gtest-param-util.h \
  include/gtest/internal/gtest-death-test-internal.h \
  include/gtest/internal/gtest-string.h \
  include/gtest/internal/custom/gtest.h \
  include/gtest/internal/custom/gtest-port.h \
  include/gtest/internal/custom/gtest-printers.h \
  include/gtest/gtest-test-part.h \
  include/gtest/gtest_prod.h \
  include/gtest/gtest-message.h \
  include/gtest/gtest-param-test.h \
  include/gtest/gtest-matchers.h \
  include/gtest/gtest-death-test.h

EXTRA_DIST = $(GTEST_SRC)

# Build rules for libraries.
lib_LTLIBRARIES = libgtest.la libgtest_main.la

libgtest_la_SOURCES = src/gtest-all.cc
libgtest_la_CPPFLAGS = -isystem $(srcdir)/include $(GTEST_CPPFLAGS)
libgtest_la_CXXFLAGS = $(GTEST_CXXFLAGS)
libgtest_la_LDFLAGS = $(GTEST_LDFLAGS)
libgtest_la_LIBADD = $(GTEST_LIBS)

libgtest_main_la_SOURCES = src/gtest_main.cc
libgtest_main_la_CPPFLAGS = -isystem $(srcdir)/include $(GTEST_CPPFLAGS)
libgtest_main_la_CXXFLAGS = $(GTEST_CXXFLAGS)
libgtest_main_la_LDFLAGS = $(GTEST_LDFLAGS)
libgtest_main_la_LIBADD = libgtest.la $(GTEST_LIBS)
