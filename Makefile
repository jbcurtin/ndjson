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

TARGET=$(BUILD_DIR)/libNDJson.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

#all: $(TARGET) $(SO_TARGET)
#$(TARGET): CFLAGS += -fPIC
#$(TARGET): build $(OBJECTS)
#	ar rcs $@ $(OBJECTS)
#	ranlib $@

#$(SO_TARGET): $(TARGET) $(OBJECTS)
#	$(CC) -shared -o $@ $(OBJECTS)

valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log"

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
main_tests: $(OBJECTS)
	$(CC) tests/$@.c -o tests/$@ -Isrc -Ilib ./src/*.o ./lib/*.o -lcurl
tests: main_tests
	sh ./tests/runtests.sh

#CFLAGS=./lib/*.o -Ilib -g -std=c99 -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
#CFLAGS=-Ilib -Isrc -g -std=c99 -O2 -Wall -Wextra -rdynamic

