/**
 * @file reduction.cpp
 * @brief Demonstrates parallel reduction techniques using OpenMP
 * @author Joseph Kehoe
 * @date 22/10/2023
 * @copyright GPL-3.0
 */

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <functional>  /* function type */
#include <limits>
#include <vector>      /* vectors used instead of arrays */
#include <omp.h>
using namespace std ;


const int LENGTH=2000;
int NumThreads=1;

/**
 * @brief Return how many threads are running
 * @return The number of threads
 */
int get_num_threads(void) {
    int num_threads = 1;
    //must ask in parallel region otherwise 1 is returned
    #pragma omp parallel
    {
        #pragma omp single
        num_threads = omp_get_num_threads();
    }
    return num_threads;
}

/**
 * @brief Calculates the sum of a vector 
 * @param data The vector of integers
 * @return The sum of the vector elements
 */
float getSerialSum(vector<int> data){
  float sum=0.0;
  for(auto& value:data){
    sum+=value;
  }
  return sum;
}

/**
 * @brief Calculates the sum of a vector in parallel
 * @param data The vector to be summed 
 * @return The sum of the vector
 */
float getParallelSum(vector<int> data){
  float sum=0.0;
#pragma omp parallel for reduction(+:sum)
  for(int i=0;i<data.size();++i){
    sum+=data[i];
  }
  return sum;
}

/**
 * @brief Calculates the sum of elements in a vector in a tiled parallel manner
 * @param data The vector of integers
 * @return The sum of the vector elements
 */
float getTiledParallelsum(vector<int> data){
  float result =0.0;
  NumThreads=get_num_threads();
  float tileResult[NumThreads];
  for(int i=0;i<NumThreads;++i) tileResult[i]=0.0;
  //map step here
#pragma omp parallel for 
  for (int i=0; i < data.size(); ++i ){
    int tid = omp_get_thread_num();
    tileResult[tid] =tileResult[tid]+data[i];
  }
  //reude step here
  for (int i=0; i < NumThreads ; ++i ){
    std::cout << i<< ":"<< tileResult[i] << "- ";
    result+=tileResult[i];
  }
  std::cout <<std::endl;
  return result ;
}

int main(void){
  float sum=0.0;
  int average=0;
  NumThreads=omp_get_num_threads();
  srand (time(NULL));
  vector<int> data(1000);
  for(auto& value:data){
    value=10;//rand()%1000;
  }

  sum=getSerialSum(data);
  average=sum/data.size();
  cout <<"Serial Average is: "<<average<<endl;
  sum=getParallelSum(data);
  average=sum/data.size();
  cout <<"Parallel Average is: "<<average<<endl;
  cout << endl;
  sum=getTiledParallelsum(data);
  average=sum/data.size();
  cout <<"Parallel Average is: "<<average<<endl;
  cout << endl;
}
// 
// reduction.cpp ends here
