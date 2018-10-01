CXXFLAGS_NORMAL=-Wall -Werror -pedantic -ggdb -O0 -std=c++11 -Iproduct
CXX=g++

.phony: all clean

all: Socket Client Main

clean:
	@rm -rf Server *.o

Socket: socket.cpp
	@$(CXX) -c -g $(CXXFLAGS_NORMAL) socket.cpp

Client: client.cpp
	@$(CXX) -c -g $(CXXFLAGS_NORMAL) client.cpp

Main: main.cpp
	@$(CXX) -c -g $(CXXFLAGS_NORMAL) main.cpp
	@$(CXX) $(CXXFLAGS_NORMAL)  main.o socket.o client.o -o Server