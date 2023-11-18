/*
Author: Liam Durkan
Student Number: C00264405
Date: 25/09/2023
Licence: GPL3
Description: 
*/

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

/*! displays a message first*/
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();//tell taskTwo to start now
}

/*! displays a message second*/
void taskTwo(std::shared_ptr<Semaphore> theSemaphore){
  theSemaphore->Wait();//wait here until taskOne finishes...
  std::cout <<"This ";
  std::cout << "will ";
  sleep(5);
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}


int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore(0));
  sem->Signal();sem->Wait();//these serve no purpose
  /**< Launch the threads  */
  int taskOneDelay=5;
  threadOne=std::thread(taskTwo,sem);
  threadTwo=std::thread(taskOne,sem,taskOneDelay);
  std::cout << "Launched from the main\n";
   /**< Wait for the threads to finish */
  threadOne.join();
  threadTwo.join();
  
  /*! Check that both threads are rejoined with the main */
  if(threadOne.joinable() == false && threadTwo.joinable() == false){
    std::cout << "Both threads have finished and rejoined with the main thread!\n";
  }
  
  return 0;
}
