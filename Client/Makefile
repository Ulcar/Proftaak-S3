TEST_HARNASS=$(wildcard tests/harnass/*.cpp)
TEST_SOURCES=$(wildcard tests/*.cpp)
TEST_HEADERS=$(wildcard includes/*.h) \
			 $(wildcard includes/*/*.h) \
			 $(wildcard *.ino)

TEST_TARGET=client_test

LFLAGS=-lgtest -lgmock -lgmock_main -lpthread
CFLAGS=-std=c++11 -Wall -Werror -g -O0 -I./
CC=g++

.PHONY: clean
clean:
	@ rm -f $(TEST_TARGET)

.PHONY: compile
compile:
	@ arduino-cli compile -b ${BOARD}

.PHONY: run
run: compile
	@ arduino-cli upload -p ${TTY} -b ${BOARD}

.PHONY: test
test: $(TEST_HARNASS) $(TEST_SOURCES) $(TEST_HEADERS)
	@ $(CC) $(CFLAGS) $(LFLAGS) $(TEST_HARNASS) $(TEST_SOURCES) -o $(TEST_TARGET)
	@ ./$(TEST_TARGET)
