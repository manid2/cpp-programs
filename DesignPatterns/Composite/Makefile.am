# Automake created by Mani Kumar

AM_CPPFLAGS = -I$(srcdir)/inc

# build lib
lib_LTLIBRARIES = libCompositeDesignPatterns.la
libCompositeDesignPatterns_la_LDFLAGS = -version-info 1:0:0
# lib headers
libCompositeDesignPatterns_la_SOURCES = \
  inc/cgraphic.h \
  inc/corganization.h
# lib sources
libCompositeDesignPatterns_la_SOURCES += \
  src/corganization.cpp \
  src/cgraphic.cpp

# build bins
bin_PROGRAMS = CompositeDesignPatterns

CompositeDesignPatterns_SOURCES = main.cpp
CompositeDesignPatterns_LDADD = libCompositeDesignPatterns.la

# build test-bin
#test_Lcc_SOURCES = test/test_stringproblems.cpp
