# Automake created by Mani Kumar

AM_CPPFLAGS = -I$(srcdir)/inc

# build lib
lib_LTLIBRARIES = libComposite.la
libComposite_la_LDFLAGS = -version-info 1:0:0
# lib headers
libComposite_la_SOURCES = \
  inc/cgraphic.h \
  inc/corganization.h
# lib sources
libComposite_la_SOURCES += \
  src/corganization.cpp \
  src/cgraphic.cpp

# build bins
bin_PROGRAMS = Composite

Composite_SOURCES = main.cpp
Composite_LDADD = libComposite.la

# build test-bin
#test_Lcc_SOURCES = test/test_stringproblems.cpp
