/**
 * @file helloThreads.cpp
 * @brief Use OpenMP to print concurrently
 * @author Joseph Kehoe
 * @date 22/10/2023
 * @copyright GPL-3.0
 */

// OpenMP header
#include <omp.h>

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Main function where multiple threads print in parallel

 */
int main(int argc, char* argv[])
{

	// Beginning of parallel region
	#pragma omp parallel
	{

		printf("Hello World... from thread = %d\n",
			omp_get_thread_num());
	}
	// Ending of parallel region
}


// 
// helloThreads.cpp ends here
