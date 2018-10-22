SHELL = /bin/sh

CXX = g++
CXXFLAGS = -g -Wextra -Werror -Wall -I include -std=c++11
LDFLAGS = -g
TARGET = client

SRC_DIR = src
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCS))

all: $(TARGET)

.PHONY: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo "Cleaning shizzles..."
	@rm $(BIN_DIR)/*.o
	@rm $(TARGET)

