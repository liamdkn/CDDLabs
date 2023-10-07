Welcome to the README file for lab 1 of Concurrent Programming. 

# Table of Contents
1. [Information](#project-licence-gpl3)
2. [To Do](#to-do)
3. [Included Files](#files-included-in-this-project)
4. [How to install](#to-install-this-project)
5. [How to execute](#how-to-complie-and-run-the-project)

## Information

#### Project Licence: 
GPL3

#### Project Author: 
Original Author: Joseph Keohe<br>
Makefile and modifications: Liam Durkan

## To install this project
1. Check that gcc is installed on the machine. I am using using version 11.0.3 
2. Create a clone of the repositiory
3. Open a terminal and navigate to the project directory. 


## Files included in this project:
- Makefile - Complies helloThreads.cpp, mutualEx.cpp & Semaphore.cpp and creates an executable 
- helloThreads.cpp - C++ file to demonstrate using semaphores. 
- mutualEx.cpp - C++11 file using mutex and condition variables to implement an example of a rendezvous for threads
- Semaphore.cpp - Uses C++11 features such as mutex and condition variables to implement Semaphore
- Semaphore.h - Header file using C++11 features such as mutex and condition variables to implement Semaphore
- README - This file. Contaning information for Lab1, how to install, compile & execute 

## How to complie and run the project
Prerequisites: [How to install](#to-install-this-project)
1. Open a new terminal and navigate to the repositorys directory.
2. To complie and create an executable for helloThreads & mutualEx type make in the terminal. 
3. To compile and create an executable for helloThreads type make helloThreads in the terminal
4. To compile and create an executable for mutualEx type make mutualEx in the terminal
5. To clean up .o files created by the project, type make CLEAN in the terminal. 