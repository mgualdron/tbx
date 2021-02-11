#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(
    [tbx],
    [0.0.1],
    [https://github.com/mgualdron/tbx/issues],
    [tbx],
    [https://github.com/mgualdron/tbx])

AC_CONFIG_SRCDIR([src/tbx.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

# AutoMake
AM_INIT_AUTOMAKE([1.11 subdir-objects])
AC_CONFIG_FILES([Makefile])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB([csv], [csv_parse])
AC_CHECK_LIB([fort], [ft_create_table])

# Checks for header files.
AC_CHECK_HEADERS([locale.h stdlib.h string.h wchar.h])
AC_CHECK_HEADER([csv.h], , [AC_MSG_ERROR(
[Could not find the csv header file. If csv.h is in a non-standard \
location, you can add it by setting your CPPFLAGS variable when running \
configure (./configure CPPFLAGS=-I/my/dir/include). Note that if you \
also need to add the library location, append LDFLAGS=-L/my/dir/lib as well.])])
AC_CHECK_HEADER([fort.h], , [AC_MSG_ERROR(
[Could not find the fort header file. If fort.h is in a non-standard \
location, you can add it by setting your CPPFLAGS variable when running \
configure (./configure CPPFLAGS=-I/my/dir/include). Note that if you \
also need to add the library location, append LDFLAGS=-L/my/dir/lib as well.])])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([memset setlocale strdup strndup strstr])

AC_OUTPUT

echo \
"-----------------------------------------------------------
Thank you for installing ${PACKAGE_NAME} version ${PACKAGE_VERSION}.

Installation directory prefix: '${prefix}'.
Compilation command: '${CC} ${CFLAGS} ${CPPFLAGS}'

To build, test, and install the program, type the following:

    make
    make check
    make install

------------------------------------------------------------"
