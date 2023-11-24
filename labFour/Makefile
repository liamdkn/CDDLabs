#Author: Liam Durkan  
#Licence: GPL3 
#Github: https://github.com/liamdkn/ConcurrentDevelopment-/blob/main/labFour

#Makefile used to contain commands to compile helloThreads & mutualEx

#Setting variables
CC = g++ 
CFLAGS = -std=c++11 -pthread 
MUTTFILES = mutualEx.cpp Semaphores.cpp Semaphore.h #list of files for the program 
TARGETS = helloThreads mutualEx

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

#rule to run all targets 

ALL: main.o Semaphore.o
	$(CC) $(CFLAGS) -o program main.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS)


#Debug rule containing debug flags 
DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL 

#Release rule with optimization flags
RELEASE: DEBUGFLAGS = -O2
RELEASE: ALL

#Remove temporary .o files
CLEAN:
	rm $(TARGETS) *.o

