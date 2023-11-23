/**
 * @file quicksort.cpp
 * @brief Implementation of the quicksort algorithm using OpenMP.
 * @author Joseph Kehoe
 * @date 12/02/2019
 * @copyright GPL-3.0
 */

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <complex>      /* complex number data type */
#include <time.h>       /* time */
#include <functional>  /* function type */
#include <limits>
#include <vector>      /* vectors used instead of arrays */

using namespace std;


const int LENGTH=2000;

/**
 * @brief Partition function for quicksort
 *
 * Partitions the array into in half with a piviot, left being lower than the pivot,
 * and right being > greater 
 * @param myArray The vector to be partitioned
 * @param low The lower index of the partition
 * @param high The high index of the partition
 * @return The index of the pivot after partition
 */
int partition (vector<int>& myArray , int low , int high ){
  int pivot=myArray[high];
  int k=high;
  int i=low;
  int temp=0;
  while (i<k){
    while (myArray[i]<pivot && i<k)++i;
    while (myArray[k]>pivot && i<k)--k;
    if (i<k){
      temp=myArray[i];
      myArray[i]=myArray[k];
      myArray[k]=temp;
      i++;//do not decrement k here OR ELSE!!
    }
  }
  return i-1;
}

//template<typename T>
/**
 * @brief Quicksort algorithm to sort the vector in parallel
 * 
 * @param myArray The vector to be sorted
 * @param low The lower index of the range to be sorted
 * @param high The higher index of the range to be sorted
 * @return Returns 1
 */
int quicksort(vector<int>& myArray , int low , int high ){
  if (low<high){
    int pivot=partition(myArray,low,high);
    //really we should only do this if each partition is above a certain size (1000 elements?)
    //otherwise the overhead outweighs any gains from using threads
    #pragma omp task shared(myArray)
    quicksort(myArray,low,pivot);
    quicksort(myArray,pivot+1,high);
    #pragma omp taskwait
  return 1;
  }
}//quicksort



int main(void){
  srand (time(NULL));
  vector<int> data(LENGTH);
  for(auto& value:data){
    value=rand()%1000;
  }
  for(auto& value:data){
    cout<<value<<" ";
  }
  cout << endl<<"*******************************"<<endl;
  quicksort(data,0,data.size()-1);
  for(auto& value:data){
    cout<<value<<" ";
  }
  cout << endl;
}
// 
// quicksort.cpp ends here
