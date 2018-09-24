CXXFLAGS_NORMAL=-Wall -Werror -pedantic -ggdb -O0 -std=c++98 -Iproduct
CXX=g++

.phony: all clean

all: Socket Client Main

clean:
	@rm -rf client socket *.o

Socket: socket.cpp
	@$(CXX) -c -g $(CXXFLAGS_NORMAL) socket.cpp
	@$(CXX) $(CXXFLAGS_NORMAL)  socket.o -o socket

Client: client.cpp
	@$(CXX) -c -g $(CXXFLAGS_NORMAL) client.cpp
	@$(CXX) $(CXXFLAGS_NORMAL)  client.o -o client

Main: main.cpp
	@$(CC) -c -g $(CFLAGS_NORMAL) main.cpp