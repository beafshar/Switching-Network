CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c 

all: network system.out switch.out

network: main.o handler.o
	$(CC) main.o handler.o $(FLAGS) -o network

main.o: main.cpp handler.h headers.h
	$(CC) $(COMPILE_FLAGS) main.cpp

system.out: system.o 
	$(CC) system.o $(FLAGS) -o system.out

switch.out: switch.o 
	$(CC) switch.o $(FLAGS) -o switch.out

system.o: system.cpp system.h headers.h
	$(CC) $(COMPILE_FLAGS) system.cpp

switch.o: switch.cpp switch.h headers.h
	$(CC) $(COMPILE_FLAGS) switch.cpp

handler.o: handler.cpp handler.h headers.h
	$(CC) $(COMPILE_FLAGS) handler.cpp

.PHONY: clean

clean:
	rm *.o *.out network