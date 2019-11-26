#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([learn-autotools], [1.0], [learn-autotools@pff.com])

# Create build-aux & build-aux/m4 dir
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])

# Init automake
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

# Create config files
AC_CONFIG_SRCDIR([DesignPatterns/Builder/main.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AR

# Init libtool
LT_INIT

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strstr])

# Create Makefiles
AC_CONFIG_FILES([
 Makefile
 DesignPatterns/Makefile
 DesignPatterns/Builder/Makefile
 DesignPatterns/Composite/Makefile
])

AC_OUTPUT
