/**
 * @file main.cpp
 * @author Liam Durkan (C00264405)
 * @brief An Implementation of a barrier Using Semaphores 
 * @date 07/10/2023
 * @copyright GPL-3.0
 */

#include "Barrier.h"
#include "Semaphore.h"
#include <thread>
#include <vector>


Semaphore barrierSem();

/*! \fn task
 *  \brief An Implementation of a resuable barrier.
 * displays the first function in the barrier being executed.
 */
/*!  */
void task(std::shared_ptr<Barrier> barrierObj){

  for(int i = 0; i < 5; ++i){
    std::cout << "first\n";
    barrierObj->waitForAll();
    std::cout << "second\n";
    barrierObj->waitForAll();
  }
}


/*!
 * \brief Main function.
 * Creates 5 threads to execute task, then rejoins the threads
 *
 * \return 0 on successful execution.
 */
int main(void){

  /*!< An array of threads*/
  std::vector<std::thread> threadArray(5);
  /*!< Pointer to barrier object*/
  std::shared_ptr<Barrier> barrierObj( new Barrier);

  barrierObj->setCount(5);

  for(int i=0; i < threadArray.size(); i++){
    threadArray[i]=std::thread(task,barrierObj);
  }

  for(int i = 0; i < threadArray.size(); i++){
    threadArray[i].join();
  }
  
  return 0;
}
