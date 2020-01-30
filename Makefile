#VPATH=./src:./include
#INCLUDES=-I./include
CC=g++
TARGET=arun
CPP_FLAGS= -Wall -O0 -g -std=c++0x
BIN = build/linux

$(TARGET): main.o sparse.o 
	$(CC) $^ -o $@
main.o : main.cpp
	$(CC) $(CPP_FLAGS) $< -c
sparse.o : sparse.cpp sparse.hpp
	$(CC) $(CPP_FLAGS) $< -c

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
	