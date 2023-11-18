/**
 * @file helloThreads.cpp
 * @author Liam Durkan (C00264405)
 * @brief Using mutex and condition variables to implement a Semaphore.
 * @date 25/09/2023
 * @copyright GPL-3.0
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <unistd.h>

/*!
 * \brief Print the first message.
 *
 * \param theSemaphore A shared pointer to the Semaphore object.
 * \param delay The delay before printing the message.
 */
void taskOne(std::shared_ptr<Semaphore> theSemaphore, int delay){
  sleep(delay);
  std::cout <<"I ";
  std::cout << "must ";
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  theSemaphore->Signal();//tell taskTwo to start now
}

/*!
 * \brief Print the second message.
 *
 * \param theSemaphore A shared pointer to the Semaphore object.
 * \param delay The delay before printing the message.
 */
void taskTwo(std::shared_ptr<Semaphore> theSemaphore, int delay){
  theSemaphore->Wait();//wait here until taskOne finishes...
  std::cout <<"This ";
  std::cout << "will ";
  sleep(delay);
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

/*!
 * \brief Main function.
 *
 * Launches two threads, One for each task, 
 *synchronising  so the first thread completes task 1 before the second thread beings task 2.
 * \return 0 on successful execution.
 */
int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> sem( new Semaphore(0));
  sem->Signal();sem->Wait();//these serve no purpose
  /**< Launch the threads  */
  int taskDelay=5;
  threadOne=std::thread(taskTwo,sem, taskDelay);
  threadTwo=std::thread(taskOne,sem,taskDelay);
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
