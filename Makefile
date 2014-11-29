-include config.mk
# Pathing Varibles
EXTERNAL_LIBS=external-libs
LIB_DIR=lib

# Compiler Opts
CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/libNDJson.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

all: $(TARGET) $(SO_TARGET) tests
$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log"

build:
	@mkdir -p build
	@mkdir -p bin

deps:
	mkdir -p lib
	mkdir -p external-libs
	cd external-libs && hg clone ssh://hg@bitbucket.org/jbcurtin/jsmn
	cd external-libs/jsmn && make test && make
	cp $(EXTERNAL_LIBS)/jsmn/jsmn.h lib/
	cp $(EXTERNAL_LIBS)/jsmn/libjsmn.a lib/

clean-deps:
	rm -rf external-libs
	rm -rf lib

clean:
	rm -rf build
	rm -rf bin

clean-all:
	make clean
	make clean-deps

