#CXXFLAGS_NORMAL=-Wall -Werror -pedantic -ggdb -O0 -std=c++11 -Iproduct -pthread
#CXX=g++
#
#.phony: all clean
#
#all: Socket Client Protocol Main
#
#clean:
#	@rm -rf Server *.o
#
#Socket: socket.cpp
#	@$(CXX) -c -g $(CXXFLAGS_NORMAL) socket.cpp
#
#Client: client.cpp
#	@$(CXX) -c -g $(CXXFLAGS_NORMAL) client.cpp
#
#Protocol: protocol.cpp
#	@$(CXX) -c -g $(CXXFLAGS_NORMAL) protocol.cpp
#
#Main: main.cpp
#	@$(CXX) -c -g $(CXXFLAGS_NORMAL) main.cpp 
#	@$(CXX) $(CXXFLAGS_NORMAL)  main.o socket.o client.o protocol.o -o Server

PRODUCT= Server

CPPFLAGS=-IInterfaces -IEnums -IProduct -IStatics
CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -std=c++11 -pthread $(CPPFLAGS)

SOURCES=$(wildcard *.cpp) \
        $(wildcard Interfaces/*.cpp) \
        $(wildcard Enums/*.cpp) \
        $(wildcard Statics/*.cpp)

HEADERS=$(wildcard *.h) \
        $(wildcard Interfaces/*.h) \
        $(wildcard Enums/*.h) \
        $(wildcard Statics/*.h)

CXX=g++

.PHONY: all clean test

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $(PRODUCT)

clean:
	@rm -rf $(PRODUCT)

test: $(PRODUCT)
	@./$(PRODUCT)
