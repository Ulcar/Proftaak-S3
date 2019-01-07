CXXFLAGS_NORMAL=-Wall -Werror -pedantic -ggdb -O0 -std=c++11 -pthread -Iproduct
CXX=g++

.phony: all clean

all: Server Client

clean:
	@rm -rf client server *.o

Server: server.cpp protocol.h
	@$(CXX) -c -g $(CXXFLAGS_NORMAL) server.cpp
	@$(CXX) $(CXXFLAGS_NORMAL)  server.o -o server

Client: client.cpp protocol.h
	@$(CXX) -c -g $(CXXFLAGS_NORMAL) client.cpp
	@$(CXX) $(CXXFLAGS_NORMAL)  client.o -o client