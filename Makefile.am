ACLOCAL_AMFLAGS = -I m4 --install
AM_CFLAGS = -g -O2 -std=gnu99 -Wall -Wextra
SUBDIRS = lib

noinst_LIBRARIES = build/libutil.a
build_libutil_a_SOURCES = src/util/darray.c src/util/darray.h src/util/dbg.h src/util/csv.c src/util/csv.h src/util/fort.c src/util/fort.h
build_libutil_a_CPPFLAGS = -I$(top_srcdir)/src -DNDEBUG

dist_man_MANS = man/tbx.1

bin_PROGRAMS = bin/tbx
bin_tbx_SOURCES = src/tbx.c
bin_tbx_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)/lib -DNDEBUG
bin_tbx_LDADD = build/libutil.a lib/libgnu.a

check_PROGRAMS = tests/darray_tests
tests_darray_tests_SOURCES = tests/darray_tests.c tests/minunit.h
tests_darray_tests_CPPFLAGS = -I$(top_srcdir)/src -DNDEBUG
tests_darray_tests_LDADD = build/libutil.a
TESTS = $(check_PROGRAMS)

EXTRA_DIST = m4/NOTES m4/gnulib-cache.m4
