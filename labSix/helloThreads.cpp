// helloThreads.cpp --- 
// 
// Filename: helloThreads.cpp
// Description: 
// Author: Joseph
// Maintainer: 
// Created: Sun Oct 22 20:36:51 2023 (+0100)
// Last-Updated: Sun Oct 22 20:37:01 2023 (+0100)
//           By: Joseph
//     Update #: 1
// 
// 

// Commentary: 
// 
// 
// 
// 
// 
// 
// 
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with GNU Emacs.  If not, see <http://www.gnu.org/licenses/>.
// 
// 

// Code:

// OpenMP program to print Hello World
// using C language

// OpenMP header
#include <omp.h>

#include <stdio.h>
#include <stdlib.h>

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