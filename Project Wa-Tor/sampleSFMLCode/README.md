## Wator Simulation

- The goal of this project is to implement a simulation using openMP for parallelization. The simulation must show a simple graphical output representing the population at each steps.

-Note: I could not get openMP working on my machine, this submission only contains the serial version. 

-Machine: Macbook, 4-Cores, 8GB Ram. 

## Information

#### Project Licence: 
 - GPL-3.0

#### Project Author: 
 - Author: Liam Durkan<br>
 - [My GitHib](https://github.com/liamdkn/CDDLabs/tree/main/Project%20Wa-Tor)

## To install this project
1. Check that gcc is installed on the machine. I am using using version 11.0.3 
2. Create a clone of the repositiory
3. Open a terminal and navigate to the project directory. 


## Files included in this project:
- Makefile - Complies main.cpp and creates and executable 'Wator'
- main.cpp - The file containing the main function. This main function is a serial implementation. 
- README - This file. Contaning information for Lab, how to install, compile & execute 

## How to complie and run the project
1. Open a new terminal and navigate to the repositories directory.
2. To complie and create an executable for wator type make in the terminal. 
5. To compile and create a release version type make RELEASE in the terminal.
6. To compile and create a debug version type make DEBUG in the terminal.
7. To clean up .o files created by the project, type make CLEAN in the terminal. 

## Testing
#### Outputs: 
- Printing to the console when shark and fish are breeding