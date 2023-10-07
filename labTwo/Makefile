#Liam Durkan 7/10/2023
#Secomnd make file version 

CC=g++
CFLAGS= -std=c++11 -pthread
MUTTFILES = rendezvous.cpp Semaphore.cpp Semaphore.h

SIMPLE: $(MUTTFILES)
	$(CC) $(CFLAGS) Semaphore.cpp rendezvous.cpp -o my_program


CLEAN:

	rm *.o
