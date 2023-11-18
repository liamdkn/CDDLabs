/**
 * @file mutualEx.cpp
 * @author Liam Durkan (C00264405)
 * @brief Using mutex and condition variables to implement an example of a rendezvous for threads.
 * @date 25/09/2023
 * @copyright GPL-3.0
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>


static const int num_threads = 100;
int sharedVariable=0;
std::mutex mtx;


/*! \fn updateTask
 *  \brief An Implementation of Mutual Exclusion using Semaphores
 * Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads
 */
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> firstSem, int numUpdates){
  firstSem -> Wait(); //lock semaphore preventing more than 1 thread passing
  for(int i=0;i<numUpdates;i++){
     std::lock_guard<std::mutex> lock(mtx);
      sharedVariable++;
  }
}

/*!
 * \brief Main function.
 *
 * Launches 100 threads, each thread increases a shared variable guarded with a semaphore. 
 *
 * \return 0 on successful execution.
 */
int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore);
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
    aSemaphore->Signal();//unlock the semaphore after teh shared variable is updated
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
