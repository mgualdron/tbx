CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG -DFT_HAVE_WCHAR $(OPTFLAGS)
INCLUDES=-I $(HOME)/local/include -L $(HOME)/local/lib
LIBS=libtbx.a
PREFIX?=$(HOME)/local

# SOURCES_LIB=src/darray.c src/tb_funcs.c
SOURCES_LIB=src/darray.c
OBJECTS_LIB=$(patsubst %.c,%.o,$(SOURCES_LIB))

SOURCES_BIN=src/tbx.c

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET_LIB=build/libtbx.a
TARGET_BIN=bin/tbx

# The Target Build
all: $(TARGET_LIB) tests $(TARGET_BIN)

dev: CFLAGS=-g -Wall -Isrc -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET_LIB): CFLAGS += -fPIC
$(TARGET_LIB): build $(OBJECTS_LIB)
	ar rcs $@ $(OBJECTS_LIB)
	ranlib $@

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests:
	$(CC) $(CFLAGS) -o tests/darray_tests tests/darray_tests.c $(TARGET_LIB)
	sh ./tests/runtests.sh

# The main executable
$(TARGET_BIN):
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(SOURCES_BIN) $(TARGET_LIB) -lfort -l:libcsv.a

# The Cleaner
clean:
	rm -rf bin build $(OBJECTS_LIB) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(PREFIX)/bin/
	install $(TARGET_BIN) $(PREFIX)/bin/
	install -d $(PREFIX)/man/man1/
	install man/tbx.1 $(PREFIX)/man/man1/

# The Checker
check:
	@echo Files with potentially dangerous functions:
	@egrep '[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)' $(SOURCES_LIB) $(SOURCES_BIN) || true
