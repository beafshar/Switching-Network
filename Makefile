CC = g++
FLAGS = -std=c++11
COMPILE_FLAGS = $(FLAGS) -c 

all: network

network: main.o system.o switch.o handler.o
	$(CC) main.o system.o switch.o handler.o $(FLAGS) -o network

main.o: main.cpp system.h switch.h handler.h headers.h
	$(CC) $(COMPILE_FLAGS) main.cpp

system.o: system.cpp system.h headers.h
	$(CC) $(COMPILE_FLAGS) system.cpp

switch.o: switch.cpp switch.h headers.h
	$(CC) $(COMPILE_FLAGS) switch.cpp

handler.o: handler.cpp handler.h headers.h
	$(CC) $(COMPILE_FLAGS) handler.cpp

.PHONY: clean

clean:
	rm *.o network