CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c 

all: switch

switch: main.o switch.o
	$(CC) main.o switch.o $(FLAGS) -o switch

main.o: main.cpp switch.h
	$(CC) $(COMPILE_FLAGS) main.cpp

switch.o: switch.cpp switch.h
	$(CC) $(COMPILE_FLAGS) switch.cpp

.PHONY: clean

clean:
	rm *.o switch