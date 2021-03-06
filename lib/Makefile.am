## DO NOT EDIT! GENERATED AUTOMATICALLY!
## Process this file with automake to produce Makefile.in.
# Copyright (C) 2002-2021 Free Software Foundation, Inc.
#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This file is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this file.  If not, see <https://www.gnu.org/licenses/>.
#
# As a special exception to the GNU General Public License,
# this file may be distributed as part of a program that
# contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
# Reproduce by:
# gnulib-tool --import \
#  --lib=libgnu \
#  --source-base=lib \
#  --m4-base=m4 \
#  --doc-base=doc \
#  --tests-base=tests \
#  --aux-dir=build-aux \
#  --no-conditional-dependencies \
#  --no-libtool \
#  --macro-prefix=gl \
#  --no-vc-files \
#  c32isprint \
#  c32rtomb \
#  mbrtoc32 \
#  uniwidth/u8-width

AUTOMAKE_OPTIONS = 1.11 gnits subdir-objects

SUBDIRS =
noinst_HEADERS =
noinst_LIBRARIES =
noinst_LTLIBRARIES =
EXTRA_DIST =
BUILT_SOURCES =
SUFFIXES =
MOSTLYCLEANFILES = core *.stackdump
MOSTLYCLEANDIRS =
CLEANFILES =
DISTCLEANFILES =
MAINTAINERCLEANFILES =
# No GNU Make output.

AM_CPPFLAGS =
AM_CFLAGS =

noinst_LIBRARIES += libgnu.a

libgnu_a_SOURCES =
libgnu_a_LIBADD = $(gl_LIBOBJS)
libgnu_a_DEPENDENCIES = $(gl_LIBOBJS)
EXTRA_libgnu_a_SOURCES =

## begin gnulib module absolute-header

# Use this preprocessor expression to decide whether #include_next works.
# Do not rely on a 'configure'-time test for this, since the expression
# might appear in an installed header, which is used by some other compiler.
HAVE_INCLUDE_NEXT = (__GNUC__ || __clang__ || 60000000 <= __DECC_VER)

## end   gnulib module absolute-header

## begin gnulib module attribute


EXTRA_DIST += attribute.h

## end   gnulib module attribute

## begin gnulib module c32isprint

libgnu_a_SOURCES += c32isprint.c

EXTRA_DIST += c32is-impl.h

## end   gnulib module c32isprint

## begin gnulib module c32rtomb


EXTRA_DIST += c32rtomb.c

EXTRA_libgnu_a_SOURCES += c32rtomb.c

## end   gnulib module c32rtomb

## begin gnulib module hard-locale

libgnu_a_SOURCES += hard-locale.c

EXTRA_DIST += hard-locale.h

## end   gnulib module hard-locale

## begin gnulib module inttypes-incomplete

BUILT_SOURCES += inttypes.h

# We need the following in order to create <inttypes.h> when the system
# doesn't have one that works with the given compiler.
inttypes.h: inttypes.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(WARN_ON_USE_H) $(ARG_NONNULL_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's/@''HAVE_INTTYPES_H''@/$(HAVE_INTTYPES_H)/g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_INTTYPES_H''@|$(NEXT_INTTYPES_H)|g' \
	      -e 's/@''APPLE_UNIVERSAL_BUILD''@/$(APPLE_UNIVERSAL_BUILD)/g' \
	      -e 's/@''PRIPTR_PREFIX''@/$(PRIPTR_PREFIX)/g' \
	      -e 's/@''GNULIB_IMAXABS''@/$(GNULIB_IMAXABS)/g' \
	      -e 's/@''GNULIB_IMAXDIV''@/$(GNULIB_IMAXDIV)/g' \
	      -e 's/@''GNULIB_STRTOIMAX''@/$(GNULIB_STRTOIMAX)/g' \
	      -e 's/@''GNULIB_STRTOUMAX''@/$(GNULIB_STRTOUMAX)/g' \
	      -e 's/@''HAVE_DECL_IMAXABS''@/$(HAVE_DECL_IMAXABS)/g' \
	      -e 's/@''HAVE_DECL_IMAXDIV''@/$(HAVE_DECL_IMAXDIV)/g' \
	      -e 's/@''HAVE_DECL_STRTOIMAX''@/$(HAVE_DECL_STRTOIMAX)/g' \
	      -e 's/@''HAVE_DECL_STRTOUMAX''@/$(HAVE_DECL_STRTOUMAX)/g' \
	      -e 's/@''HAVE_IMAXDIV_T''@/$(HAVE_IMAXDIV_T)/g' \
	      -e 's/@''REPLACE_STRTOIMAX''@/$(REPLACE_STRTOIMAX)/g' \
	      -e 's/@''REPLACE_STRTOUMAX''@/$(REPLACE_STRTOUMAX)/g' \
	      -e 's/@''INT32_MAX_LT_INTMAX_MAX''@/$(INT32_MAX_LT_INTMAX_MAX)/g' \
	      -e 's/@''INT64_MAX_EQ_LONG_MAX''@/$(INT64_MAX_EQ_LONG_MAX)/g' \
	      -e 's/@''UINT32_MAX_LT_UINTMAX_MAX''@/$(UINT32_MAX_LT_UINTMAX_MAX)/g' \
	      -e 's/@''UINT64_MAX_EQ_ULONG_MAX''@/$(UINT64_MAX_EQ_ULONG_MAX)/g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/inttypes.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += inttypes.h inttypes.h-t

EXTRA_DIST += inttypes.in.h

## end   gnulib module inttypes-incomplete

## begin gnulib module limits-h

BUILT_SOURCES += $(LIMITS_H)

# We need the following in order to create <limits.h> when the system
# doesn't have one that is compatible with GNU.
if GL_GENERATE_LIMITS_H
limits.h: limits.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_LIMITS_H''@|$(NEXT_LIMITS_H)|g' \
	      < $(srcdir)/limits.in.h; \
	} > $@-t && \
	mv $@-t $@
else
limits.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += limits.h limits.h-t

EXTRA_DIST += limits.in.h

## end   gnulib module limits-h

## begin gnulib module localcharset

libgnu_a_SOURCES += localcharset.c

EXTRA_DIST += localcharset.h

## end   gnulib module localcharset

## begin gnulib module locale

BUILT_SOURCES += locale.h

# We need the following in order to create <locale.h> when the system
# doesn't have one that provides all definitions.
locale.h: locale.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_LOCALE_H''@|$(NEXT_LOCALE_H)|g' \
	      -e 's/@''GNULIB_LOCALECONV''@/$(GNULIB_LOCALECONV)/g' \
	      -e 's/@''GNULIB_SETLOCALE''@/$(GNULIB_SETLOCALE)/g' \
	      -e 's/@''GNULIB_SETLOCALE_NULL''@/$(GNULIB_SETLOCALE_NULL)/g' \
	      -e 's/@''GNULIB_DUPLOCALE''@/$(GNULIB_DUPLOCALE)/g' \
	      -e 's/@''GNULIB_LOCALENAME''@/$(GNULIB_LOCALENAME)/g' \
	      -e 's|@''HAVE_NEWLOCALE''@|$(HAVE_NEWLOCALE)|g' \
	      -e 's|@''HAVE_DUPLOCALE''@|$(HAVE_DUPLOCALE)|g' \
	      -e 's|@''HAVE_FREELOCALE''@|$(HAVE_FREELOCALE)|g' \
	      -e 's|@''HAVE_XLOCALE_H''@|$(HAVE_XLOCALE_H)|g' \
	      -e 's|@''REPLACE_LOCALECONV''@|$(REPLACE_LOCALECONV)|g' \
	      -e 's|@''REPLACE_SETLOCALE''@|$(REPLACE_SETLOCALE)|g' \
	      -e 's|@''REPLACE_NEWLOCALE''@|$(REPLACE_NEWLOCALE)|g' \
	      -e 's|@''REPLACE_DUPLOCALE''@|$(REPLACE_DUPLOCALE)|g' \
	      -e 's|@''REPLACE_FREELOCALE''@|$(REPLACE_FREELOCALE)|g' \
	      -e 's|@''REPLACE_STRUCT_LCONV''@|$(REPLACE_STRUCT_LCONV)|g' \
	      -e 's|@''LOCALENAME_ENHANCE_LOCALE_FUNCS''@|$(LOCALENAME_ENHANCE_LOCALE_FUNCS)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/locale.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += locale.h locale.h-t

EXTRA_DIST += locale.in.h

## end   gnulib module locale

## begin gnulib module mbrtoc32


EXTRA_DIST += lc-charset-dispatch.c lc-charset-dispatch.h mbrtoc32.c mbrtowc-impl-utf8.h mbrtowc-impl.h mbtowc-lock.c mbtowc-lock.h windows-initguard.h

EXTRA_libgnu_a_SOURCES += lc-charset-dispatch.c mbrtoc32.c mbtowc-lock.c

## end   gnulib module mbrtoc32

## begin gnulib module mbrtowc


EXTRA_DIST += lc-charset-dispatch.c lc-charset-dispatch.h mbrtowc-impl-utf8.h mbrtowc-impl.h mbrtowc.c mbtowc-lock.c mbtowc-lock.h windows-initguard.h

EXTRA_libgnu_a_SOURCES += lc-charset-dispatch.c mbrtowc.c mbtowc-lock.c

## end   gnulib module mbrtowc

## begin gnulib module mbsinit


EXTRA_DIST += mbsinit.c

EXTRA_libgnu_a_SOURCES += mbsinit.c

## end   gnulib module mbsinit

## begin gnulib module setlocale-null

libgnu_a_SOURCES += setlocale_null.c

EXTRA_DIST += setlocale-lock.c setlocale_null.h windows-initguard.h

EXTRA_libgnu_a_SOURCES += setlocale-lock.c

## end   gnulib module setlocale-null

## begin gnulib module snippet/arg-nonnull

# Because this Makefile snippet defines a variable used by other
# gnulib Makefile snippets, it must be present in all makefiles that
# need it. This is ensured by the applicability 'all' defined above.

ARG_NONNULL_H=$(srcdir)/arg-nonnull.h

EXTRA_DIST += arg-nonnull.h

## end   gnulib module snippet/arg-nonnull

## begin gnulib module snippet/c++defs

# Because this Makefile snippet defines a variable used by other
# gnulib Makefile snippets, it must be present in all makefiles that
# need it. This is ensured by the applicability 'all' defined above.

CXXDEFS_H=$(srcdir)/c++defs.h

EXTRA_DIST += c++defs.h

## end   gnulib module snippet/c++defs

## begin gnulib module snippet/unused-parameter

# Because this Makefile snippet defines a variable used by other
# gnulib Makefile snippets, it must be present in all makefiles that
# need it. This is ensured by the applicability 'all' defined above.

UNUSED_PARAMETER_H=$(srcdir)/unused-parameter.h

EXTRA_DIST += unused-parameter.h

## end   gnulib module snippet/unused-parameter

## begin gnulib module snippet/warn-on-use

# Because this Makefile snippet defines a variable used by other
# gnulib Makefile snippets, it must be present in all makefiles that
# need it. This is ensured by the applicability 'all' defined above.

WARN_ON_USE_H=$(srcdir)/warn-on-use.h

EXTRA_DIST += warn-on-use.h

## end   gnulib module snippet/warn-on-use

## begin gnulib module stdbool

BUILT_SOURCES += $(STDBOOL_H)

# We need the following in order to create <stdbool.h> when the system
# doesn't have one that works.
if GL_GENERATE_STDBOOL_H
stdbool.h: stdbool.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's/@''HAVE__BOOL''@/$(HAVE__BOOL)/g' < $(srcdir)/stdbool.in.h; \
	} > $@-t && \
	mv $@-t $@
else
stdbool.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += stdbool.h stdbool.h-t

EXTRA_DIST += stdbool.in.h

## end   gnulib module stdbool

## begin gnulib module stddef

BUILT_SOURCES += $(STDDEF_H)

# We need the following in order to create <stddef.h> when the system
# doesn't have one that works with the given compiler.
if GL_GENERATE_STDDEF_H
stddef.h: stddef.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */' && \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_STDDEF_H''@|$(NEXT_STDDEF_H)|g' \
	      -e 's|@''HAVE_MAX_ALIGN_T''@|$(HAVE_MAX_ALIGN_T)|g' \
	      -e 's|@''HAVE_WCHAR_T''@|$(HAVE_WCHAR_T)|g' \
	      -e 's|@''REPLACE_NULL''@|$(REPLACE_NULL)|g' \
	      < $(srcdir)/stddef.in.h; \
	} > $@-t && \
	mv $@-t $@
else
stddef.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += stddef.h stddef.h-t

EXTRA_DIST += stddef.in.h

## end   gnulib module stddef

## begin gnulib module stdint

BUILT_SOURCES += $(STDINT_H)

# We need the following in order to create <stdint.h> when the system
# doesn't have one that works with the given compiler.
if GL_GENERATE_STDINT_H
stdint.h: stdint.in.h $(top_builddir)/config.status
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's/@''HAVE_STDINT_H''@/$(HAVE_STDINT_H)/g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_STDINT_H''@|$(NEXT_STDINT_H)|g' \
	      -e 's/@''HAVE_C99_STDINT_H''@/$(HAVE_C99_STDINT_H)/g' \
	      -e 's/@''HAVE_SYS_TYPES_H''@/$(HAVE_SYS_TYPES_H)/g' \
	      -e 's/@''HAVE_INTTYPES_H''@/$(HAVE_INTTYPES_H)/g' \
	      -e 's/@''HAVE_SYS_INTTYPES_H''@/$(HAVE_SYS_INTTYPES_H)/g' \
	      -e 's/@''HAVE_SYS_BITYPES_H''@/$(HAVE_SYS_BITYPES_H)/g' \
	      -e 's/@''HAVE_WCHAR_H''@/$(HAVE_WCHAR_H)/g' \
	      -e 's/@''APPLE_UNIVERSAL_BUILD''@/$(APPLE_UNIVERSAL_BUILD)/g' \
	      -e 's/@''BITSIZEOF_PTRDIFF_T''@/$(BITSIZEOF_PTRDIFF_T)/g' \
	      -e 's/@''PTRDIFF_T_SUFFIX''@/$(PTRDIFF_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_SIG_ATOMIC_T''@/$(BITSIZEOF_SIG_ATOMIC_T)/g' \
	      -e 's/@''HAVE_SIGNED_SIG_ATOMIC_T''@/$(HAVE_SIGNED_SIG_ATOMIC_T)/g' \
	      -e 's/@''SIG_ATOMIC_T_SUFFIX''@/$(SIG_ATOMIC_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_SIZE_T''@/$(BITSIZEOF_SIZE_T)/g' \
	      -e 's/@''SIZE_T_SUFFIX''@/$(SIZE_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_WCHAR_T''@/$(BITSIZEOF_WCHAR_T)/g' \
	      -e 's/@''HAVE_SIGNED_WCHAR_T''@/$(HAVE_SIGNED_WCHAR_T)/g' \
	      -e 's/@''WCHAR_T_SUFFIX''@/$(WCHAR_T_SUFFIX)/g' \
	      -e 's/@''BITSIZEOF_WINT_T''@/$(BITSIZEOF_WINT_T)/g' \
	      -e 's/@''HAVE_SIGNED_WINT_T''@/$(HAVE_SIGNED_WINT_T)/g' \
	      -e 's/@''WINT_T_SUFFIX''@/$(WINT_T_SUFFIX)/g' \
	      -e 's/@''GNULIB_OVERRIDES_WINT_T''@/$(GNULIB_OVERRIDES_WINT_T)/g' \
	      < $(srcdir)/stdint.in.h; \
	} > $@-t && \
	mv $@-t $@
else
stdint.h: $(top_builddir)/config.status
	rm -f $@
endif
MOSTLYCLEANFILES += stdint.h stdint.h-t

EXTRA_DIST += stdint.in.h

## end   gnulib module stdint

## begin gnulib module streq


EXTRA_DIST += streq.h

## end   gnulib module streq

## begin gnulib module sys_types

BUILT_SOURCES += sys/types.h

# We need the following in order to create <sys/types.h> when the system
# doesn't have one that works with the given compiler.
sys/types.h: sys_types.in.h $(top_builddir)/config.status
	$(AM_V_at)$(MKDIR_P) sys
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_SYS_TYPES_H''@|$(NEXT_SYS_TYPES_H)|g' \
	      -e 's|@''WINDOWS_64_BIT_OFF_T''@|$(WINDOWS_64_BIT_OFF_T)|g' \
	      -e 's|@''WINDOWS_STAT_INODES''@|$(WINDOWS_STAT_INODES)|g' \
	      < $(srcdir)/sys_types.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += sys/types.h sys/types.h-t

EXTRA_DIST += sys_types.in.h

## end   gnulib module sys_types

## begin gnulib module uchar

BUILT_SOURCES += uchar.h

uchar.h: uchar.in.h $(top_builddir)/config.status $(CXXDEFS_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's/@''HAVE_UCHAR_H''@/$(HAVE_UCHAR_H)/g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_UCHAR_H''@|$(NEXT_UCHAR_H)|g' \
	      -e 's|@''CXX_HAS_UCHAR_TYPES''@|$(CXX_HAS_UCHAR_TYPES)|g' \
	      -e 's|@''SMALL_WCHAR_T''@|$(SMALL_WCHAR_T)|g' \
	      -e 's|@''GNULIB_OVERRIDES_CHAR16_T''@|$(GNULIB_OVERRIDES_CHAR16_T)|g' \
	      -e 's|@''GNULIB_OVERRIDES_CHAR32_T''@|$(GNULIB_OVERRIDES_CHAR32_T)|g' \
	      -e 's/@''GNULIB_BTOC32''@/$(GNULIB_BTOC32)/g' \
	      -e 's/@''GNULIB_C32ISALNUM''@/$(GNULIB_C32ISALNUM)/g' \
	      -e 's/@''GNULIB_C32ISALPHA''@/$(GNULIB_C32ISALPHA)/g' \
	      -e 's/@''GNULIB_C32ISBLANK''@/$(GNULIB_C32ISBLANK)/g' \
	      -e 's/@''GNULIB_C32ISCNTRL''@/$(GNULIB_C32ISCNTRL)/g' \
	      -e 's/@''GNULIB_C32ISDIGIT''@/$(GNULIB_C32ISDIGIT)/g' \
	      -e 's/@''GNULIB_C32ISGRAPH''@/$(GNULIB_C32ISGRAPH)/g' \
	      -e 's/@''GNULIB_C32ISLOWER''@/$(GNULIB_C32ISLOWER)/g' \
	      -e 's/@''GNULIB_C32ISPRINT''@/$(GNULIB_C32ISPRINT)/g' \
	      -e 's/@''GNULIB_C32ISPUNCT''@/$(GNULIB_C32ISPUNCT)/g' \
	      -e 's/@''GNULIB_C32ISSPACE''@/$(GNULIB_C32ISSPACE)/g' \
	      -e 's/@''GNULIB_C32ISUPPER''@/$(GNULIB_C32ISUPPER)/g' \
	      -e 's/@''GNULIB_C32ISXDIGIT''@/$(GNULIB_C32ISXDIGIT)/g' \
	      -e 's/@''GNULIB_C32RTOMB''@/$(GNULIB_C32RTOMB)/g' \
	      -e 's/@''GNULIB_C32SNRTOMBS''@/$(GNULIB_C32SNRTOMBS)/g' \
	      -e 's/@''GNULIB_C32SRTOMBS''@/$(GNULIB_C32SRTOMBS)/g' \
	      -e 's/@''GNULIB_C32STOMBS''@/$(GNULIB_C32STOMBS)/g' \
	      -e 's/@''GNULIB_C32TOB''@/$(GNULIB_C32TOB)/g' \
	      -e 's/@''GNULIB_MBRTOC32''@/$(GNULIB_MBRTOC32)/g' \
	      -e 's/@''GNULIB_MBSNRTOC32S''@/$(GNULIB_MBSNRTOC32S)/g' \
	      -e 's/@''GNULIB_MBSRTOC32S''@/$(GNULIB_MBSRTOC32S)/g' \
	      -e 's/@''GNULIB_MBSTOC32S''@/$(GNULIB_MBSTOC32S)/g' \
	      -e 's|@''HAVE_C32RTOMB''@|$(HAVE_C32RTOMB)|g' \
	      -e 's|@''HAVE_MBRTOC32''@|$(HAVE_MBRTOC32)|g' \
	      -e 's|@''REPLACE_C32RTOMB''@|$(REPLACE_C32RTOMB)|g' \
	      -e 's|@''REPLACE_MBRTOC32''@|$(REPLACE_MBRTOC32)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      < $(srcdir)/uchar.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += uchar.h uchar.h-t

EXTRA_DIST += uchar.in.h

## end   gnulib module uchar

## begin gnulib module unictype/base

BUILT_SOURCES += $(LIBUNISTRING_UNICTYPE_H)

unictype.h: unictype.in.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  cat $(srcdir)/unictype.in.h; \
	} > $@-t && \
	mv -f $@-t $@
MOSTLYCLEANFILES += unictype.h unictype.h-t

EXTRA_DIST += unictype.in.h

## end   gnulib module unictype/base

## begin gnulib module unictype/ctype-print

if LIBUNISTRING_COMPILE_UNICTYPE_CTYPE_PRINT
libgnu_a_SOURCES += unictype/ctype_print.c
endif

EXTRA_DIST += unictype/bitmap.h unictype/ctype_print.h

## end   gnulib module unictype/ctype-print

## begin gnulib module unistr/base

BUILT_SOURCES += $(LIBUNISTRING_UNISTR_H)

unistr.h: unistr.in.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  cat $(srcdir)/unistr.in.h; \
	} > $@-t && \
	mv -f $@-t $@
MOSTLYCLEANFILES += unistr.h unistr.h-t

EXTRA_DIST += unistr.in.h

## end   gnulib module unistr/base

## begin gnulib module unistr/u8-mbtouc-unsafe

if LIBUNISTRING_COMPILE_UNISTR_U8_MBTOUC_UNSAFE
libgnu_a_SOURCES += unistr/u8-mbtouc-unsafe.c unistr/u8-mbtouc-unsafe-aux.c
endif

## end   gnulib module unistr/u8-mbtouc-unsafe

## begin gnulib module unitypes

BUILT_SOURCES += $(LIBUNISTRING_UNITYPES_H)

unitypes.h: unitypes.in.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  cat $(srcdir)/unitypes.in.h; \
	} > $@-t && \
	mv -f $@-t $@
MOSTLYCLEANFILES += unitypes.h unitypes.h-t

EXTRA_DIST += unitypes.in.h

## end   gnulib module unitypes

## begin gnulib module uniwidth/base

BUILT_SOURCES += $(LIBUNISTRING_UNIWIDTH_H)

uniwidth.h: uniwidth.in.h
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  cat $(srcdir)/uniwidth.in.h; \
	} > $@-t && \
	mv -f $@-t $@
MOSTLYCLEANFILES += uniwidth.h uniwidth.h-t

EXTRA_DIST += localcharset.h uniwidth.in.h

## end   gnulib module uniwidth/base

## begin gnulib module uniwidth/u8-width

if LIBUNISTRING_COMPILE_UNIWIDTH_U8_WIDTH
libgnu_a_SOURCES += uniwidth/u8-width.c
endif

## end   gnulib module uniwidth/u8-width

## begin gnulib module uniwidth/width

if LIBUNISTRING_COMPILE_UNIWIDTH_WIDTH
libgnu_a_SOURCES += uniwidth/width.c
endif

EXTRA_DIST += uniwidth/cjk.h

## end   gnulib module uniwidth/width

## begin gnulib module verify


EXTRA_DIST += verify.h

## end   gnulib module verify

## begin gnulib module wchar

BUILT_SOURCES += wchar.h

# We need the following in order to create <wchar.h> when the system
# version does not work standalone.
wchar.h: wchar.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(ARG_NONNULL_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''HAVE_FEATURES_H''@|$(HAVE_FEATURES_H)|g' \
	      -e 's|@''NEXT_WCHAR_H''@|$(NEXT_WCHAR_H)|g' \
	      -e 's|@''HAVE_WCHAR_H''@|$(HAVE_WCHAR_H)|g' \
	      -e 's/@''HAVE_CRTDEFS_H''@/$(HAVE_CRTDEFS_H)/g' \
	      -e 's/@''GNULIB_OVERRIDES_WINT_T''@/$(GNULIB_OVERRIDES_WINT_T)/g' \
	      -e 's/@''GNULIB_BTOWC''@/$(GNULIB_BTOWC)/g' \
	      -e 's/@''GNULIB_WCTOB''@/$(GNULIB_WCTOB)/g' \
	      -e 's/@''GNULIB_MBSINIT''@/$(GNULIB_MBSINIT)/g' \
	      -e 's/@''GNULIB_MBRTOWC''@/$(GNULIB_MBRTOWC)/g' \
	      -e 's/@''GNULIB_MBRLEN''@/$(GNULIB_MBRLEN)/g' \
	      -e 's/@''GNULIB_MBSRTOWCS''@/$(GNULIB_MBSRTOWCS)/g' \
	      -e 's/@''GNULIB_MBSNRTOWCS''@/$(GNULIB_MBSNRTOWCS)/g' \
	      -e 's/@''GNULIB_WCRTOMB''@/$(GNULIB_WCRTOMB)/g' \
	      -e 's/@''GNULIB_WCSRTOMBS''@/$(GNULIB_WCSRTOMBS)/g' \
	      -e 's/@''GNULIB_WCSNRTOMBS''@/$(GNULIB_WCSNRTOMBS)/g' \
	      -e 's/@''GNULIB_WCWIDTH''@/$(GNULIB_WCWIDTH)/g' \
	      -e 's/@''GNULIB_WMEMCHR''@/$(GNULIB_WMEMCHR)/g' \
	      -e 's/@''GNULIB_WMEMCMP''@/$(GNULIB_WMEMCMP)/g' \
	      -e 's/@''GNULIB_WMEMCPY''@/$(GNULIB_WMEMCPY)/g' \
	      -e 's/@''GNULIB_WMEMMOVE''@/$(GNULIB_WMEMMOVE)/g' \
	      -e 's/@''GNULIB_WMEMPCPY''@/$(GNULIB_WMEMPCPY)/g' \
	      -e 's/@''GNULIB_WMEMSET''@/$(GNULIB_WMEMSET)/g' \
	      -e 's/@''GNULIB_WCSLEN''@/$(GNULIB_WCSLEN)/g' \
	      -e 's/@''GNULIB_WCSNLEN''@/$(GNULIB_WCSNLEN)/g' \
	      -e 's/@''GNULIB_WCSCPY''@/$(GNULIB_WCSCPY)/g' \
	      -e 's/@''GNULIB_WCPCPY''@/$(GNULIB_WCPCPY)/g' \
	      -e 's/@''GNULIB_WCSNCPY''@/$(GNULIB_WCSNCPY)/g' \
	      -e 's/@''GNULIB_WCPNCPY''@/$(GNULIB_WCPNCPY)/g' \
	      -e 's/@''GNULIB_WCSCAT''@/$(GNULIB_WCSCAT)/g' \
	      -e 's/@''GNULIB_WCSNCAT''@/$(GNULIB_WCSNCAT)/g' \
	      -e 's/@''GNULIB_WCSCMP''@/$(GNULIB_WCSCMP)/g' \
	      -e 's/@''GNULIB_WCSNCMP''@/$(GNULIB_WCSNCMP)/g' \
	      -e 's/@''GNULIB_WCSCASECMP''@/$(GNULIB_WCSCASECMP)/g' \
	      -e 's/@''GNULIB_WCSNCASECMP''@/$(GNULIB_WCSNCASECMP)/g' \
	      -e 's/@''GNULIB_WCSCOLL''@/$(GNULIB_WCSCOLL)/g' \
	      -e 's/@''GNULIB_WCSXFRM''@/$(GNULIB_WCSXFRM)/g' \
	      -e 's/@''GNULIB_WCSDUP''@/$(GNULIB_WCSDUP)/g' \
	      -e 's/@''GNULIB_WCSCHR''@/$(GNULIB_WCSCHR)/g' \
	      -e 's/@''GNULIB_WCSRCHR''@/$(GNULIB_WCSRCHR)/g' \
	      -e 's/@''GNULIB_WCSCSPN''@/$(GNULIB_WCSCSPN)/g' \
	      -e 's/@''GNULIB_WCSSPN''@/$(GNULIB_WCSSPN)/g' \
	      -e 's/@''GNULIB_WCSPBRK''@/$(GNULIB_WCSPBRK)/g' \
	      -e 's/@''GNULIB_WCSSTR''@/$(GNULIB_WCSSTR)/g' \
	      -e 's/@''GNULIB_WCSTOK''@/$(GNULIB_WCSTOK)/g' \
	      -e 's/@''GNULIB_WCSWIDTH''@/$(GNULIB_WCSWIDTH)/g' \
	      -e 's/@''GNULIB_WCSFTIME''@/$(GNULIB_WCSFTIME)/g' \
	      -e 's/@''GNULIB_MDA_WCSDUP''@/$(GNULIB_MDA_WCSDUP)/g' \
	      < $(srcdir)/wchar.in.h | \
	  sed -e 's|@''HAVE_WINT_T''@|$(HAVE_WINT_T)|g' \
	      -e 's|@''HAVE_BTOWC''@|$(HAVE_BTOWC)|g' \
	      -e 's|@''HAVE_MBSINIT''@|$(HAVE_MBSINIT)|g' \
	      -e 's|@''HAVE_MBRTOWC''@|$(HAVE_MBRTOWC)|g' \
	      -e 's|@''HAVE_MBRLEN''@|$(HAVE_MBRLEN)|g' \
	      -e 's|@''HAVE_MBSRTOWCS''@|$(HAVE_MBSRTOWCS)|g' \
	      -e 's|@''HAVE_MBSNRTOWCS''@|$(HAVE_MBSNRTOWCS)|g' \
	      -e 's|@''HAVE_WCRTOMB''@|$(HAVE_WCRTOMB)|g' \
	      -e 's|@''HAVE_WCSRTOMBS''@|$(HAVE_WCSRTOMBS)|g' \
	      -e 's|@''HAVE_WCSNRTOMBS''@|$(HAVE_WCSNRTOMBS)|g' \
	      -e 's|@''HAVE_WMEMCHR''@|$(HAVE_WMEMCHR)|g' \
	      -e 's|@''HAVE_WMEMCMP''@|$(HAVE_WMEMCMP)|g' \
	      -e 's|@''HAVE_WMEMCPY''@|$(HAVE_WMEMCPY)|g' \
	      -e 's|@''HAVE_WMEMMOVE''@|$(HAVE_WMEMMOVE)|g' \
	      -e 's|@''HAVE_WMEMPCPY''@|$(HAVE_WMEMPCPY)|g' \
	      -e 's|@''HAVE_WMEMSET''@|$(HAVE_WMEMSET)|g' \
	      -e 's|@''HAVE_WCSLEN''@|$(HAVE_WCSLEN)|g' \
	      -e 's|@''HAVE_WCSNLEN''@|$(HAVE_WCSNLEN)|g' \
	      -e 's|@''HAVE_WCSCPY''@|$(HAVE_WCSCPY)|g' \
	      -e 's|@''HAVE_WCPCPY''@|$(HAVE_WCPCPY)|g' \
	      -e 's|@''HAVE_WCSNCPY''@|$(HAVE_WCSNCPY)|g' \
	      -e 's|@''HAVE_WCPNCPY''@|$(HAVE_WCPNCPY)|g' \
	      -e 's|@''HAVE_WCSCAT''@|$(HAVE_WCSCAT)|g' \
	      -e 's|@''HAVE_WCSNCAT''@|$(HAVE_WCSNCAT)|g' \
	      -e 's|@''HAVE_WCSCMP''@|$(HAVE_WCSCMP)|g' \
	      -e 's|@''HAVE_WCSNCMP''@|$(HAVE_WCSNCMP)|g' \
	      -e 's|@''HAVE_WCSCASECMP''@|$(HAVE_WCSCASECMP)|g' \
	      -e 's|@''HAVE_WCSNCASECMP''@|$(HAVE_WCSNCASECMP)|g' \
	      -e 's|@''HAVE_WCSCOLL''@|$(HAVE_WCSCOLL)|g' \
	      -e 's|@''HAVE_WCSXFRM''@|$(HAVE_WCSXFRM)|g' \
	      -e 's|@''HAVE_WCSDUP''@|$(HAVE_WCSDUP)|g' \
	      -e 's|@''HAVE_WCSCHR''@|$(HAVE_WCSCHR)|g' \
	      -e 's|@''HAVE_WCSRCHR''@|$(HAVE_WCSRCHR)|g' \
	      -e 's|@''HAVE_WCSCSPN''@|$(HAVE_WCSCSPN)|g' \
	      -e 's|@''HAVE_WCSSPN''@|$(HAVE_WCSSPN)|g' \
	      -e 's|@''HAVE_WCSPBRK''@|$(HAVE_WCSPBRK)|g' \
	      -e 's|@''HAVE_WCSSTR''@|$(HAVE_WCSSTR)|g' \
	      -e 's|@''HAVE_WCSTOK''@|$(HAVE_WCSTOK)|g' \
	      -e 's|@''HAVE_WCSWIDTH''@|$(HAVE_WCSWIDTH)|g' \
	      -e 's|@''HAVE_WCSFTIME''@|$(HAVE_WCSFTIME)|g' \
	      -e 's|@''HAVE_DECL_WCTOB''@|$(HAVE_DECL_WCTOB)|g' \
	      -e 's|@''HAVE_DECL_WCSDUP''@|$(HAVE_DECL_WCSDUP)|g' \
	      -e 's|@''HAVE_DECL_WCWIDTH''@|$(HAVE_DECL_WCWIDTH)|g' \
	  | \
	  sed -e 's|@''REPLACE_MBSTATE_T''@|$(REPLACE_MBSTATE_T)|g' \
	      -e 's|@''REPLACE_BTOWC''@|$(REPLACE_BTOWC)|g' \
	      -e 's|@''REPLACE_WCTOB''@|$(REPLACE_WCTOB)|g' \
	      -e 's|@''REPLACE_MBSINIT''@|$(REPLACE_MBSINIT)|g' \
	      -e 's|@''REPLACE_MBRTOWC''@|$(REPLACE_MBRTOWC)|g' \
	      -e 's|@''REPLACE_MBRLEN''@|$(REPLACE_MBRLEN)|g' \
	      -e 's|@''REPLACE_MBSRTOWCS''@|$(REPLACE_MBSRTOWCS)|g' \
	      -e 's|@''REPLACE_MBSNRTOWCS''@|$(REPLACE_MBSNRTOWCS)|g' \
	      -e 's|@''REPLACE_WCRTOMB''@|$(REPLACE_WCRTOMB)|g' \
	      -e 's|@''REPLACE_WCSRTOMBS''@|$(REPLACE_WCSRTOMBS)|g' \
	      -e 's|@''REPLACE_WCSNRTOMBS''@|$(REPLACE_WCSNRTOMBS)|g' \
	      -e 's|@''REPLACE_WCWIDTH''@|$(REPLACE_WCWIDTH)|g' \
	      -e 's|@''REPLACE_WCSWIDTH''@|$(REPLACE_WCSWIDTH)|g' \
	      -e 's|@''REPLACE_WCSFTIME''@|$(REPLACE_WCSFTIME)|g' \
	      -e 's|@''REPLACE_WCSTOK''@|$(REPLACE_WCSTOK)|g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_ARG_NONNULL/r $(ARG_NONNULL_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)'; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += wchar.h wchar.h-t

EXTRA_DIST += wchar.in.h

## end   gnulib module wchar

## begin gnulib module wcrtomb


EXTRA_DIST += wcrtomb.c

EXTRA_libgnu_a_SOURCES += wcrtomb.c

## end   gnulib module wcrtomb

## begin gnulib module wctype-h

BUILT_SOURCES += wctype.h
libgnu_a_SOURCES += wctype-h.c

# We need the following in order to create <wctype.h> when the system
# doesn't have one that works with the given compiler.
wctype.h: wctype.in.h $(top_builddir)/config.status $(CXXDEFS_H) $(WARN_ON_USE_H)
	$(AM_V_GEN)rm -f $@-t $@ && \
	{ echo '/* DO NOT EDIT! GENERATED AUTOMATICALLY! */'; \
	  sed -e 's|@''GUARD_PREFIX''@|GL|g' \
	      -e 's/@''HAVE_WCTYPE_H''@/$(HAVE_WCTYPE_H)/g' \
	      -e 's|@''INCLUDE_NEXT''@|$(INCLUDE_NEXT)|g' \
	      -e 's|@''PRAGMA_SYSTEM_HEADER''@|@PRAGMA_SYSTEM_HEADER@|g' \
	      -e 's|@''PRAGMA_COLUMNS''@|@PRAGMA_COLUMNS@|g' \
	      -e 's|@''NEXT_WCTYPE_H''@|$(NEXT_WCTYPE_H)|g' \
	      -e 's/@''HAVE_CRTDEFS_H''@/$(HAVE_CRTDEFS_H)/g' \
	      -e 's/@''GNULIB_OVERRIDES_WINT_T''@/$(GNULIB_OVERRIDES_WINT_T)/g' \
	      -e 's/@''GNULIB_ISWBLANK''@/$(GNULIB_ISWBLANK)/g' \
	      -e 's/@''GNULIB_ISWDIGIT''@/$(GNULIB_ISWDIGIT)/g' \
	      -e 's/@''GNULIB_ISWXDIGIT''@/$(GNULIB_ISWXDIGIT)/g' \
	      -e 's/@''GNULIB_WCTYPE''@/$(GNULIB_WCTYPE)/g' \
	      -e 's/@''GNULIB_ISWCTYPE''@/$(GNULIB_ISWCTYPE)/g' \
	      -e 's/@''GNULIB_WCTRANS''@/$(GNULIB_WCTRANS)/g' \
	      -e 's/@''GNULIB_TOWCTRANS''@/$(GNULIB_TOWCTRANS)/g' \
	      -e 's/@''HAVE_ISWBLANK''@/$(HAVE_ISWBLANK)/g' \
	      -e 's/@''HAVE_ISWCNTRL''@/$(HAVE_ISWCNTRL)/g' \
	      -e 's/@''HAVE_WCTYPE_T''@/$(HAVE_WCTYPE_T)/g' \
	      -e 's/@''HAVE_WCTRANS_T''@/$(HAVE_WCTRANS_T)/g' \
	      -e 's/@''HAVE_WINT_T''@/$(HAVE_WINT_T)/g' \
	      -e 's/@''REPLACE_ISWBLANK''@/$(REPLACE_ISWBLANK)/g' \
	      -e 's/@''REPLACE_ISWDIGIT''@/$(REPLACE_ISWDIGIT)/g' \
	      -e 's/@''REPLACE_ISWXDIGIT''@/$(REPLACE_ISWXDIGIT)/g' \
	      -e 's/@''REPLACE_ISWCNTRL''@/$(REPLACE_ISWCNTRL)/g' \
	      -e 's/@''REPLACE_TOWLOWER''@/$(REPLACE_TOWLOWER)/g' \
	      -e '/definitions of _GL_FUNCDECL_RPL/r $(CXXDEFS_H)' \
	      -e '/definition of _GL_WARN_ON_USE/r $(WARN_ON_USE_H)' \
	      < $(srcdir)/wctype.in.h; \
	} > $@-t && \
	mv $@-t $@
MOSTLYCLEANFILES += wctype.h wctype.h-t

EXTRA_DIST += wctype.in.h

## end   gnulib module wctype-h


mostlyclean-local: mostlyclean-generic
	@for dir in '' $(MOSTLYCLEANDIRS); do \
	  if test -n "$$dir" && test -d $$dir; then \
	    echo "rmdir $$dir"; rmdir $$dir; \
	  fi; \
	done; \
	:
