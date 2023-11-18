## Lab 3 - Reusable Barrier Class

- This lab introduces the topics of reusable barriers using semaphores.

## Information

#### Project Licence: 
 - GPL-3.0

#### Project Author: 
 - Original Author: Joseph Keohe<br>
 - Makefile and modifications: Liam Durkan
 - [My GitHib](https://github.com/liamdkn/CDDLabs)

## To install this project
1. Check that gcc is installed on the machine. I am using using version 11.0.3 
2. Create a clone of the repositiory
3. Open a terminal and navigate to the project directory. 


## Files included in this project:
- Makefile - Complies helloThreads.cpp, mutualEx.cpp & Semaphore.cpp and creates an executable 
- Semaphore.cpp - Uses C++11 features such as mutex and condition variables to implement Semaphore
- Semaphore.h - Header file using C++11 features such as mutex and condition variables to implement Semaphore
- Barrier.cpp - The implementation file for the Barrier class.
- Barrier.h - The header file for the Barrier class.
- main.cpp - The file containing the main function. This main function creates atleast two threads demonstrating a reusable barrier in action.
- README - This file. Contaning information for Lab1, how to install, compile & execute 

## How to complie and run the project
1. Open a new terminal and navigate to the repositorys directory.
2. To complie and create an executable for barrier type make in the terminal. 
5. To compile and create a release version type make RELEASE in the terminal.
6. To compile and create a debug version type make DEBUG in the terminal.
7. To clean up .o files created by the project, type make CLEAN in the terminal. 

## Testing
#### Outputs: 
first<br>
first<br>
first<br>
first<br>
first<br>
second<br>
second<br>
second<br>
second<br>
second<br>
first<br>
first<br>
first<br>
first<br>
first<br>
second<br>
second<br>
second<br>
second<br>
second<br>
first<br>
first<br>
first<br>
first<br>
first<br>
second<br>
second<br>
second<br>
second<br>
second<br>
first<br>
first<br>
first<br>
first<br>
first<br>
second<br>
second<br>
second<br>
second<br>
second<br>
first<br>
first<br>
first<br>
first<br>
first<br>
second<br>
second<br>
second<br>
second<br>
second<br>
