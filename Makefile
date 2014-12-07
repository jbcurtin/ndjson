-include config.mk
# Pathing Varibles
EXTERNAL_LIBS=external-libs
BUILD_DIR=build
LIB_DIR=lib

# Compiler Opts
CFLAGS=./lib/*.o -Ilib -g -std=c99 -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

build:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p bin

deps:
	mkdir -p lib
	mkdir -p external-libs
	cd external-libs && hg clone ssh://hg@bitbucket.org/jbcurtin/jsmn
	cd external-libs/jsmn && make test && make
	cp $(EXTERNAL_LIBS)/jsmn/jsmn.h lib/
	cp $(EXTERNAL_LIBS)/jsmn/libjsmn.a lib/
	cp $(EXTERNAL_LIBS)/jsmn/jsmn.o lib/

clean-deps:
	rm -rf external-libs
	rm -rf lib

clean:
	rm -rf $(BUILD_DIR)
	rm -rf bin

clean-all:
	make clean
	make clean-deps

### Testing ###
DEBUG_FLAGS=-O0 -g
TEST_SOURCES=$(wildcard tests/*_tests.c)
TEST_TARGETS=$(patsubst %.c,%,$(TEST_SOURCES))

test-build:
	$(CC) -Isrc -Ilib ./src/*.o ./lib/*.o -lcurl -g -c -m32
$(TEST_TARGETS): $(TEST_SOURCES) test-build
	$(CC) -o $@ -Isrc -Ilib ./src/*.o ./lib/*.o -lcurl -g $@.c -m32
tests: $(TEST_TARGETS)
	sh ./tests/runtests.sh

