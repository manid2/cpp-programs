#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([pff-dp-ext], [1.0], [pff-dp-ext@pff.com])

AC_CONFIG_SRCDIR([README.md])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])

dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
AC_LANG([C++])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
LT_INIT

dnl Check for C++11
#AC_LANG_PUSH([C++])
#AX_CXX_COMPILE_STDCXX_11([noext])
#AC_LANG_POP([C++])

dnl GCC specific configuration (optional)
GCC_WARN_CXXFLAGS="-fdiagnostics-color=auto -Wall -Wextra -Wpedantic -Wfatal-errors"
GCC_WARN_CXXFLAGS_EXTRA="-Wcast-align -Wcast-qual -Wformat -Wpointer-arith -Wwrite-strings"
GCC_DEBUG_CXXFLAGS="-g -O0 -fno-omit-frame-pointer -fno-inline"

dnl Check for GCC warning flags (optional)
AC_MSG_CHECKING([whether to enable the GCC warnings])
AC_ARG_ENABLE([gcc-warnings],
    [AS_HELP_STRING([--enable-gcc-warnings],
                    [turn on GCC warnings for development])],
    [case "$enableval" in
        yes|no) ;;
        *)      AC_MSG_ERROR([bad value ${enableval} for gcc-warnings option]) ;;
    esac
    gcc_warnings=$enableval],
    [gcc_warnings=no]
)
AC_MSG_RESULT([$gcc_warnings])
if test "$gcc_warnings" = yes; then
    AC_SUBST([WARN_CXXFLAGS],"$GCC_WARN_CXXFLAGS $GCC_WARN_CXXFLAGS_EXTRA")
fi

dnl Check for GCC debug flags (optional)
AC_MSG_CHECKING([whether to enable the GCC debug build])
AC_ARG_ENABLE([gcc-debug],
    [AS_HELP_STRING([--enable-gcc-debug],
                    [turn on GCC debug flags (for developers)])],
    [case "$enableval" in
        yes|no) ;;
        *)      AC_MSG_ERROR([bad value ${enableval} for gcc-debug option]) ;;
    esac
    gcc_debug=$enableval],
    [gcc_debug=no]
)
AC_MSG_RESULT([$gcc_debug])
if test "$gcc_debug" = yes; then
    AC_SUBST([CXXFLAGS],"$GCC_DEBUG_CXXFLAGS")
    AC_DEFINE([DEBUG],[],[Debug Mode])
else
    AC_DEFINE([NDEBUG],[],[Release Mode])
fi

dnl Configure pthreads.
#ACX_PTHREAD([have_pthread=yes])

# Define gtest variables
GTEST_VERSION="1.7.0"
if test "x$have_pthread" = "xyes"; then
  GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=1"
  GTEST_CXXFLAGS="$PTHREAD_CFLAGS"
  GTEST_LDFLAGS=
  GTEST_LIBS="$PTHREAD_LIBS"
else
  GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=0"
  GTEST_CXXFLAGS=
  GTEST_LDFLAGS=
  GTEST_LIBS=
fi
AC_SUBST([GTEST_VERSION])
AC_SUBST([GTEST_CPPFLAGS])
AC_SUBST([GTEST_CXXFLAGS])
AC_SUBST([GTEST_LDFLAGS])
AC_SUBST([GTEST_LIBS])

dnl Checks for header files.
AC_CHECK_HEADERS([string.h])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

dnl Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strstr])

dnl Print build help msg
AC_MSG_RESULT([
pff-dp-ext $VERSION is now configured
Configure Information:
  C Compiler      :  $CC
  DEFS            :  $DEFS
  CPPFLAGS        :  $CPPFLAGS
  CFLAGS          :  $CFLAGS

  C++ Compiler    :  $CXX
  DEFS            :  $DEFS
  CPPFLAGS        :  $CPPFLAGS
  CXXFLAGS        :  $CXXFLAGS

  Linker          :  $LD
  LDFLAGS         :  $LDFLAGS
  LIBS            :  $LIBS

  Google Test
  GTEST_CPPFLAGS  : $GTEST_CPPFLAGS
  GTEST_CXXFLAGS  : $GTEST_CXXFLAGS
  GTEST_LDFLAGS   : $GTEST_LDFLAGS
  GTEST_LIBS      : $GTEST_LIBS
])

dnl Create Makefiles
AC_CONFIG_FILES([
  Makefile \
  lib/Makefile
])

dnl Config sub-packages
AC_CONFIG_SUBDIRS([lib/googletest])

AC_OUTPUT
