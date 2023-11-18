## Lab 2 - Rendezvous

 - Using the Semaphore class create a program that demonstrates the Rendezvous pattern. <br> 
  A rendezvous occurs between two threads when there is a point (in the code) that both threads must reach before either can continue.

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
- Makefile - Complies rendezevous.cpp & Semaphore.cpp to create an executable 
- rendezevous.cpp - C++ file to demonstrate a rendezevous using Mutuexs. 
- Semaphore.cpp - Uses C++11 features such as mutex and condition variables to implement Semaphore
- Semaphore.h - Header file using C++11 features such as mutex and condition variables to implement Semaphore
- README - This file. Contaning information for Lab2, how to install, compile & execute 

## How to complie and run the project
1. Open a new terminal and navigate to the repositorys directory.
2. To complie and create an executable for rendezvous.cpp type make in the terminal.
3. To compile and create a release version type make RELEASE in the terminal.
4. To compile and create a debug version type make DEBUG in the terminal.
5. To clean up .o files created by the project, type make CLEAN in the terminal. 

## Testing
#### Outputs: 
first<br>
first<br>
first<br>
first<br>
first<br><br>
second<br>
second<br>
second<br>
second<br>
second<br>

