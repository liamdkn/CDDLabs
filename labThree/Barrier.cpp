#include "Barrier.h"

/*! \class Barrier
    \brief An Implementation of a barrier Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement a barrier using Semaphores with N number threads

*/
/*! Barrier constructor*/
Barrier::Barrier(){

  this->count = 0;
  threadNum = 0;
  condition = false;

  mutex=std::make_shared<Semaphore>(1);
  
  entryBarrier = std::make_shared<Semaphore>(0);
  exitBarrier = std::make_shared<Semaphore>(1);

}
/*! Barrier with parameter constructor*/
Barrier::Barrier(int count){

  this->count = count;
  threadNum = 0;
  condition = false;

  mutex=std::make_shared<Semaphore>(1);

  entryBarrier = std::make_shared<Semaphore>(0);
  exitBarrier = std::make_shared<Semaphore>(1);
}
/*! Barrier deconstructor*/
Barrier::~Barrier(){

}

/*! sets count value*/
void Barrier::setCount(int x){

  this->count = x;
}
/*! returns count value*/
int Barrier::getCount(){

  return this->count;
}

/*! waits for all the threads before starting second half of code*/ 
void Barrier::waitForAll(){

  mutex->Wait(); //enter the critical section
  threadNum++; //increase threads that have arrived 

  if(threadNum == count){ //if last thread arrives 
    entryBarrier->Signal(); //tell entry barrier to close 
    threadNum = 0; //reset thread numbers 
    exitBarrier->Signal();
  }
  mutex->Signal(); //release mutex lock

  entryBarrier->Wait(); //wait for all threads to arrive at entry barrier
  entryBarrier->Signal(); //
}
