/**
 * @file rendezvous.cpp
 * @author Liam Durkan (C00264405)
 * @brief A Semaphore Implementation
 * @date 7/10/2023
 * @copyright GPL-3.0
 */

#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

int arrivedThreads = 0;

/*!
 * \fn task
 * \brief displays the first function in the barrier being executed
 * \param mutexSem A shared pointer to a Semaphore object.
 * \param barrierSem A shared pointer to a Semaphore object.
 * \param threadCount Count arrived threads
 */
void task(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, int threadCount){
  mutexSem->Wait(); //Open the critical section
  std::cout << "first" << std::endl;  //demonstrate threads completing task
  ++arrivedThreads;  //Increase arrived thread count

  if (arrivedThreads == threadCount) { //If all threads have arrived 
      mutexSem->Signal(); //Release the lock
      barrierSem->Signal(); //signal the barrier semaphore to proceed
  }
  else{ //Not all threads have arrived at the first step
    mutexSem->Signal(); //Release the lock
    barrierSem->Wait(); //Wait for the barrier semaphore to proceed
  }

  mutexSem->Wait(); //Open the critical section
  std::cout << "second" << std::endl;
  mutexSem->Signal(); //Release critical section lock
  barrierSem->Signal(); 
}

/*!
 * \brief Main function.
 * Launches five threads to execute a task() synchronously/
 * Initalises 2 semaphores 
 * \return 0 on successful execution.
 */
int main(void){
  std::shared_ptr<Semaphore> mutexSem;
  std::shared_ptr<Semaphore> barrierSem;
  int threadCount = 5;
  mutexSem=std::make_shared<Semaphore>(1);
  barrierSem=std::make_shared<Semaphore>(0);
  /*!< An array of threads*/
  std::vector<std::thread> threadArray(threadCount);
  /*!< Pointer to barrier object*/

  for(int i=0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,mutexSem,barrierSem,threadCount);
  }

  for(int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}
