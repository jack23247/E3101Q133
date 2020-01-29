VPATH=./src:./include
INCLUDES=-I./include
CC=g++
TARGET=arun
CPP_FLAGS= -Wall -O0 -g -std=c++0x

build/linux/$(TARGET): main.o dip.o 
	$(CC) $^ -o $@
build/linux/main.o : main.cpp
	$(CC) $(CPP_FLAGS) $(INCLUDES) $< -c
build/linux/sparse.o : sparse.hpp
	$(CC) $(CPP_FLAGS) $(INCLUDES) $< -c

.PHONY: clean
clean:
	rm -rf *.o $(TARGET)
	