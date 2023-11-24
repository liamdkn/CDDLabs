## Lab 1 - The Basics 

- The lab introduces the topic of openMP using algorithims. 

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
- Makefile - Complies each cpp file and creates an executable 
- mandelbroit.cpp - Implementation of the Mandelbrot set calculation using OpenMP parallelization.
- reduction.cpp - Demonstrates parallel reduction techniques using OpenMP
- quicksort.cpp - Implementation of the quicksort algorithm using OpenMP.
- helloThreads.cpp - Use OpenMP to print concurrently
- README - This file. Contaning information for Lab6, how to install, compile & execute 

## How to complie and run the project
1. Open a new terminal and navigate to the repositorys directory.
2. To complie and create an executable, navigate to the folder directory and type make in the terminal  
3. To compile and create a release version type make RELEASE in the terminal.
4. To compile and create a debug version type make DEBUG in the terminal.
5. To clean up .o files created by the project, type make CLEAN in the terminal. 

# Examples of Map Pattern

Map is the simplest pattern.  It is embarrisingly parallel with no need for any data sharing between threads.

Two examples are included here with code showing how to get timing results demonstrating speedup.

## SAXPY

This is a standard algorithm used a lot in simulation.
It  stands for Single-precision y := alpha * x + y where alpha is a scalar and x and y are n-vectors. SAXPY is a combination of scalar multiplication and vector addition, and it’s very simple: it takes as input two vectors of 32-bit floats X and Y with N elements each, and a scalar value A. It multiplies each element X[i] by A and adds the result to Y[i]. There are Double and Complex data type versions as well - DAxpy, Caxpy, Zaxpy.

## Mandelbroit Set

The Mandelbrot set is a two-dimensional set with a relatively simple definition that exhibits great complexity, especially as it is magnified. It is popular for its aesthetic appeal and fractal structures. The set is defined in the complex plane as the complex numbers c c for which the function  f_{c}(z)=z^{2}+c  does not diverge to infinity when iterated starting at z = 0 z=0, i.e., for which the sequence f_{c}(0)}, f_{c}(f_{c}(0))}, etc., remains bounded in absolute value.

This set was first defined and drawn by Robert W. Brooks and Peter Matelski in 1978, as part of a study of Kleinian groups.[3] Afterwards, in 1980, Benoit Mandelbrot obtained high-quality visualizations of the set while working at IBM's Thomas J. Watson Research Center in Yorktown Heights, New York. [label](https://en.wikipedia.org/wiki/Mandelbrot_set)

