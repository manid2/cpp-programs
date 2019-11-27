# Automake created by Mani Kumar

AM_CPPFLAGS = -I$(srcdir)/inc

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
