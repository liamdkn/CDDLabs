#Author: Liam Durkan 7/10/2023
#Licence: GPL-3.0 
#Github: https://github.com/liamdkn/ConcurrentDevelopment-/blob/main/labTwo


#Setting variables
CC=g++
CFLAGS= -std=c++11 -pthread
MUTTFILES = rendezvous.cpp Semaphore.cpp Semaphore.h #list of files for the program 

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

SIMPLE: rendezvous.o Semaphore.o 
	$(CC) $(CFLAGS) -o rendezvous Semaphore.cpp rendezvous.cpp $(DEBUGFLAGS) 

#Debug rule containing debug flags 
DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: SIMPLE

#Release rule with optimization flags
RELEASE: DEBUGFLAGS = -O2
RELEASE: SIMPLE

#Remove temporary .o files
CLEAN:
	rm  *.o