CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c 

all: system

system: main.o system.o
	$(CC) main.o system.o $(FLAGS) -o system

main.o: main.cpp system.h
	$(CC) $(COMPILE_FLAGS) main.cpp

system.o: system.cpp system.h
	$(CC) $(COMPILE_FLAGS) system.cpp

.PHONY: clean

clean:
	rm *.o system