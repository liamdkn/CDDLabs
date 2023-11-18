/**
 * @file barrier.cpp
 * @author Liam Durkan (C00264405)
 * @date 07/10/2023
 * @copyright GPL-3.0
 */

#include "Barrier.h"

/*! \class Barrier
    \brief An Implementation of a barrier Using Semaphores 

   Uses C++11 features such as mutex and condition variables to implement a barrier using Semaphores with N number threads

*/
/*! Barrier constructor*/
Barrier::Barrier(){

  this->count = 5;
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
  threadNum++; //increase threads arrived 
  if(threadNum == count){ //if last thread arrives 
    exitBarrier->Wait();//close exit gate
    entryBarrier->Signal();//allow all threads into airlock 
  }
  mutex->Signal(); //release mutex lock

  entryBarrier->Wait();
  entryBarrier->Signal();
  
  mutex->Wait();
  --threadNum;

  if(threadNum == 0){
    entryBarrier->Wait();
    exitBarrier->Signal();
  }
  mutex->Signal();

  exitBarrier->Wait(); //wait for all threads to arrive at entry barrier
  exitBarrier->Signal();

}
