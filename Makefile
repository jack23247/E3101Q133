#VPATH=./src:./include
#INCLUDES=-I./include
CC=g++
TARGET=arun
CPP_FLAGS= -Wall -O0 -g -std=c++0x
BIN = build/linux

$(TARGET): main.o
	$(CC) $^ -o $@
main.o : main.cpp sparse.hpp
	$(CC) $(CPP_FLAGS) -c main.cpp -o main.o


.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
