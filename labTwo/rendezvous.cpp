#include "Semaphore.h"
#include <thread>
#include <vector>
#include <iostream>

int arrived = 0;
Semaphore mutexSem(0);
Semaphore barrierSem(1);

/*! displays the first function in the barrier being executed */
void task(std::shared_ptr<Semaphore> mutexSem,std::shared_ptr<Semaphore> barrierSem, int threadCount){

    mutexSem->Wait();  // Open the critical section
    std::cout << "first" << std::endl; //Thread in the CS performs a function
    ++arrived;//increase variable that thread arrived 

    if (arrived == threadCount) {
        // If all threads have arrived, signal the barrier semaphore to proceed
        barrierSem->Signal();// Signal that the thread has arrived at the rendezvous point
    }
    else{
      mutexSem->Signal();  // Release the mutual exclusion lock
    }

    barrierSem->Wait();  // Wait for the barrier semaphore to proceed


    std::cout << "second" << std::endl;
    barrierSem->Signal();
}




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
