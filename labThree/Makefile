#Author: Liam Durkan 
#Licence: GPL3 
#Github: https://github.com/liamdkn/ConcurrentDevelopment-/blob/main/labThree


#Setting variables
CC=g++
CFLAGS= -std=c++11 -pthread
MUTTFILES = Barrier.cpp Semaphore.cpp Semaphore.h  main.cpp#list of files for the program 

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

SIMPLE: Semaphore.o Barrier.o main.o
	$(CC) -o barrier Semaphore.o Barrier.o main.o $(CFLAGS) $(DEBUGFLAGS) 

#Debug rule containing debug flags 
DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: SIMPLE

#Release rule with optimization flags
RELEASE: DEBUGFLAGS = -O2
RELEASE: SIMPLE

#Remove temporary .o files
CLEAN:
	rm  *.o