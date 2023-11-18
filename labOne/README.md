## Lab 1 - The Basics 

- This lab introduces the topics of mutex and condition variables to implement a Semaphore &   rendezvous for threads. 

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
- helloThreads.cpp - C++ file to demonstrate using semaphores. 
- mutualEx.cpp - C++11 file using mutex and condition variables to implement an example of a rendezvous for threads
- Semaphore.cpp - Uses C++11 features such as mutex and condition variables to implement Semaphore
- Semaphore.h - Header file using C++11 features such as mutex and condition variables to implement Semaphore
- README - This file. Contaning information for Lab1, how to install, compile & execute 

## How to complie and run the project
1. Open a new terminal and navigate to the repositorys directory.
2. To complie and create an executable for helloThreads & mutualEx type make in the terminal. 
3. To compile and create an executable for helloThreads type make helloThreads in the terminal
4. To compile and create an executable for mutualEx type make mutualEx in the terminal.
5. To compile and create a release version type make RELEASE in the terminal.
6. To compile and create a debug version type make DEBUG in the terminal.
7. To clean up .o files created by the project, type make CLEAN in the terminal. 

## Testing
#### helloThreads
- Outputs: 'I must print first' followed by 'This will appear second'
- If both threads rejoin the main, they are no longer 'joinable' then the terminal will output <br>
'Both threads have finished and rejoined with the main thread!'<br>

#### mutaulEx
- Outputs: 100000 