#Author: Liam Durkan \
Student Number: C00264405 \
Date: 25/09/2023 \
Licence: GPL-3.0 \
Description: Makefile used to contain commands to compile helloThreads & mutualEx \
GitHub: https://github.com/liamdkn/CDDLabs


#Setting variables
CC = g++ 
CFLAGS = -std=c++11 -pthread 
MUTTFILES = mutualEx.cpp Semaphores.cpp Semaphore.h #list of files for the program 
TARGETS = helloThreads mutualEx

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

#rule to run all targets 
ALL: $(TARGETS)

helloThreads: helloThreads.o Semaphore.o  # Add HelloThreads.o & Semaphore.o as a dependency
	$(CC) $(CFLAGS) -o helloThreads helloThreads.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS)

mutualEx: mutualEx.o Semaphore.o  # Add mutualExclusion.o & Semaphore.o as a dependency
	$(CC) $(CFLAGS) -o mutualEx mutualEx.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS)

#Debug rule containing debug flags 
DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: ALL 

#Release rule with optimization flags
RELEASE: DEBUGFLAGS = -O2
RELEASE: ALL

#Remove temporary .o files
CLEAN:
	rm $(TARGETS) *.o

