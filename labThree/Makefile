CC=g++
CFLAGS= -std=c++11 -pthread -I.

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: Semaphore.o Barrier.o main.o
	$(CC) -o barrier Semaphore.o Barrier.o main.o $(CFLAGS) $(DEBUGFLAGS) 

DEBUG: DEBUGFLAGS = -g -O0
DEBUG: ALL

CLEAN:
	rm *.o
