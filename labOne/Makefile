#Liam Durkan 25/09/2023
#Second improved Makefile
#Used to contain commands to compile projects


CC = g++
CFLAGS = -std=c++11 -pthread
MUTTFILES = mutualEx.cpp Semaphores.cpp Semaphore.h

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: helloThreads.o Semaphore.o  # Add Semaphore.o as a dependency
	$(CC) $(CFLAGS) -o helloThreads helloThreads.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS) #Link Semaphore.o

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL

#This is customary and just deletes all .o files
CLEAN:
	rm *.o
