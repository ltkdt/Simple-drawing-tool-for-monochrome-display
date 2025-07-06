CC=g++
CFLAGS=-g

LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
INC=-I../include

BUILD=../build

SRC=src

program: main.cpp logic_handle.cpp file_handle.cpp
	$(CC) $(INC) main.cpp file_handle.cpp logic_handle.cpp -o $(BUILD)/program $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(BUILD)/program