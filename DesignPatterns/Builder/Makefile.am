# Automake created by Mani Kumar

AM_CPPFLAGS = -I$(srcdir)/inc

# build lib
lib_LTLIBRARIES = libBuilderDesignPattern.la
libBuilderDesignPattern_la_LDFLAGS = -version-info 1:0:0
# lib headers
libBuilderDesignPattern_la_SOURCES = \
  inc/carbuilder.h \
  inc/cburgerbuilder.h \
  inc/cxmlbuilder.h \
  inc/cxmldombuilder.h
# lib sources
libBuilderDesignPattern_la_SOURCES += \
  src/carbuilder.cpp \
  src/cburgerbuilder.cpp \
  src/cxmlbuilder.cpp \
  src/cxmldombuilder.cpp

# build bins
bin_PROGRAMS = BuilderDesignPattern

BuilderDesignPattern_SOURCES = main.cpp
BuilderDesignPattern_LDADD = libBuilderDesignPattern.la

# build test-bin
#test_Lcc_SOURCES = test/test_stringproblems.cpp
