#Liam Durkan 25/09/2023
#Makefile used to contain commands to compile helloThreads & mutualEx


#Setting variables
CC = g++ 
CFLAGS = -std=c++11 -pthread 
MUTTFILES = mutualEx.cpp Semaphores.cpp Semaphore.h #list of files for the program 

#This rule says that each .o file depends on a .cpp file of the same name
%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(DEBUGFLAGS)

#rule to run both othe rules
ALL: helloThreads mutualEx

helloThreads: helloThreads.o Semaphore.o  # Add HelloThreads.o & Semaphore.o as a dependency
	$(CC) $(CFLAGS) -o helloThreads helloThreads.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS)

mutualEx: mutualEx.o Semaphore.o  # Add mutualExclusion.o & Semaphore.o as a dependency
	$(CC) $(CFLAGS) -o mutualEx mutualEx.o Semaphore.o $(CFLAGS) $(DEBUGFLAGS)

DEBUG: DEBUGFLAGS = -DDEBUG
DEBUG: helloThreads mutualEx

#Remove temporary .o files
CLEAN:
	rm helloThreads.o Semaphore.o