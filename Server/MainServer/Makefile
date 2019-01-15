PRODUCT= Server

CPPFLAGS=-IEnums -IInterfaces -IProduct -IStatics -IProduct/Machines -IProduct/Handlers
CXXFLAGS=-Wall -Werror -Wextra -Wno-unused-parameter -pedantic -ggdb -O0 -std=c++11 -pthread $(CPPFLAGS)
# -Wno-unused-parameter is to ignore the warning that a paramater is not used in the method

SOURCES=$(wildcard Product/*.cpp) \
        $(wildcard Product/Machines/*.cpp) \
        $(wildcard Product/Handlers/*.cpp) \
        $(wildcard Interfaces/*.cpp) \
        $(wildcard Enums/*.cpp) \
        $(wildcard Statics/*.cpp)

HEADERS=$(wildcard Product/*.h) \
        $(wildcard Product/Machines/*.h) \
        $(wildcard Product/Handlers/*.cpp) \
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
