CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c 

all: system

network: main.o system.o switch.o
	$(CC) main.o system.o switch.o $(FLAGS) -o network

main.o: main.cpp system.h switch.h headers.h
	$(CC) $(COMPILE_FLAGS) main.cpp

system.o: system.cpp system.h headers.h
	$(CC) $(COMPILE_FLAGS) system.cpp

switch.o: switch.cpp switch.h headers.h
	$(CC) $(COMPILE_FLAGS) switch.cpp

.PHONY: clean

clean:
	rm *.o system