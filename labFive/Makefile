#Author: Liam Durkan 11/11/2023
#Licence: GPL3 
#Github: https://github.com/liamdkn/ConcurrentDevelopment-/blob/main/labFive

#Makefile used to contain commands 

#Setting variables
CC = g++ 
CFLAGS = -std=c++11 -pthread 
MUTTFILES = main.cpp Semaphores.cpp Semaphore.h #list of files for the program 


#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

ALL: main.o Semaphore.o  # Add main.o & Semaphore.o as a dependency
	$(CC) $(CFLAGS) -o prodCon main.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS)

#Debug rule containing debug flags 
DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL 

#Release rule with optimization flags
RELEASE: DEBUGFLAGS = -O2
RELEASE: ALL

#Remove temporary .o files
CLEAN:
	rm *.o

