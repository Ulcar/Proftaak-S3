PRODUCT= Server

CPPFLAGS=-IEnums -IInterfaces -IProduct -IStatics -IProduct/Machines
CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -std=c++11 -pthread $(CPPFLAGS)

SOURCES=$(wildcard Product/*.cpp) \
        $(wildcard Product/Machines/*.cpp) \
        $(wildcard Interfaces/*.cpp) \
        $(wildcard Enums/*.cpp) \
        $(wildcard Statics/*.cpp)

HEADERS=$(wildcard Product/*.h) \
        $(wildcard Product/Machines/*.h) \
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
