#VPATH=./src:./include
#INCLUDES=-I./include
CC=g++
TARGET=arun
CPP_FLAGS= -Wall -O0 -g -std=c++0x
BIN = build/linux

$(TARGET): $(BIN)/main.o $(BIN)/sparse.o 
	$(CC) $^ -o $@
$(BIN)/main.o : main.cpp
	$(CC) $(CPP_FLAGS) $< -c
$(BIN)/sparse.o : sparse.hpp
	$(CC) $(CPP_FLAGS) $< -c

.PHONY: clean
clean:
	rm -rf $(BIN)/*.o $(TARGET)
	