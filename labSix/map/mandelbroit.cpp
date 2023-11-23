/**
 * @file mandelbroit.cpp
 * @brief Implementation of the Mandelbrot set calculation using OpenMP parallelization.
 * @author Joseph Kehoe
 * @date 04/02/2019
 * @copyright GPL-3.0
 */

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <limits>

using namespace std ;

const int ROW=1000;
const int COL=1000;
const int DEPTH=10;

/**
 * @brief Calculates the Mandelbrot set for a given complex number.
 *
 * @param c The complex number for which the Mandelbrot set is calculated.
 * @param depth Maximum depth of iteration for Mandelbrot calculation.
 * @return The number of iterations taken to escape the Mandelbrot set.
 */
int calc(complex<int> c, int depth){
    int count=0;
    complex<int> z=0;
    for(int i=0;i<depth;++i){
	if (abs(z)>2.0){
            break;
	}
	z=z*z+c;
	count++;
    }
    return count;
}

/**
 * @brief Calculates the Mandelbrot set for each point in the grid and stores the results in a 2D array.
 *
 * @param p The 2D array to store the Mandelbrot set results.
 * @param depth Maximum depth of iteration for Mandelbrot calculation.
 */
void mandel( int p[ROW][COL], int depth){
  #pragma omp parallel for collapse(2)	  
  for(int i=0;i<ROW;++i){
        for(int k=0;k<COL;++k){
	  p[i][k]=calc(complex<int>(i,k),depth);
	}
    }
}

/**
 * @brief Main function that initializes the random seed, calculates the Mandelbrot set, and measures the execution time.
 *
 * @return 0 if the program executes successfully.
 */
int main(void){

  
  int myArray[ROW][COL];
  /* initialize random seed: */
  srand (time(NULL));
  
  clock_t begin = clock();
  mandel(myArray,DEPTH);
  clock_t end = clock();
  double timeSec = (end - begin) / static_cast<double>( CLOCKS_PER_SEC );
  std::cout << timeSec << std::endl;
}
// 
// mandelbroit.cpp ends here
