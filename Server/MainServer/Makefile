PRODUCT= Server

CPPFLAGS=-IEnums -IInterfaces -IProduct -IStatics
CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -std=c++11 -pthread $(CPPFLAGS)

SOURCES=$(wildcard Product/*.cpp) \
        $(wildcard Interfaces/*.cpp) \
        $(wildcard Enums/*.cpp) \
        $(wildcard Statics/*.cpp)

HEADERS=$(wildcard Product/*.h) \
        $(wildcard Interfaces/*.h) \
        $(wildcard Enums/*.h) \
        $(wildcard Statics/*.h)

CXX=g++

.PHONY: all clean test

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $(PRODUCT)

clean:
	@rm -rf $(PRODUCT) *.o

test: $(PRODUCT)
	@./$(PRODUCT)
