/**
 * @file main.cpp
 * @author Liam Durkan (C00264405)
 * @brief This main function implements a solution to the Dining Philosophers problem.
 * @date 11/11/2023
 * @copyright GPL-3.0
 */

#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h>

const int COUNT = 5;
const int THINKTIME=3;
const int EATTIME=5;
std::vector<Semaphore> forks(COUNT);
std::shared_ptr<Semaphore> forkLock;

/*!
 * \fn think
 * \brief Each philosopher is waiting to get a fork
 *
 * \param myID Semaphore ID for forks 
 */
void think(int myID){
  int seconds=rand() % THINKTIME + 1;
  std::cout << myID << " is thinking! "<<std::endl;
  sleep(seconds);
}

/*!
 * \fn get_fork
 * \brief One philosopher locks two forks 
 *
 * \param myID Philosopher ID (thread count)
 */
void get_forks(int philID){
  forks[philID].Wait(); 
  forks[(philID+1)%COUNT].Wait();
  std::cout << philID << " gets fork "<<std::endl;
  
}

/*!
 * \fn put_fork
 * \brief Philosopher unlocks both forks 
 *
 * \param myID Philosopher ID (thread count)
 */
void put_forks(int philID){
  forks[philID].Signal();
  forks[(philID+1)%COUNT].Signal(); 
  std::cout << philID << " releasing fork "<<std::endl;
}

/*!
 * \fn eat
 * \brief Philosopher has 2 forks locked, therefore can eat. 
 *
 * \param myID Semaphore ID for forks 
 */
void eat(int myID){
  int seconds=rand() % EATTIME + 1;
  std::cout << myID << " is chomping! "<<std::endl;
  sleep(seconds);  
}

void philosopher(int id, std::shared_ptr<Semaphore> forkLock){
  while(true){
    forkLock->Wait();
    think(id);//every thread arrives
    get_forks(id); //get & lock two forks
    eat(id); 
    put_forks(id); //release locked forks
    forkLock->Signal();

  }//while  
}//philosopher



int main(void){
  srand (time(NULL)); // initialize random seed: 

  for(Semaphore& s : forks){
    s.Signal(); // make all forks avaliable 
  }

  std::vector<std::thread> vt(COUNT);
  forkLock = std::make_shared<Semaphore>(4);

  int id=0;
  for(std::thread& t: vt){
    t=std::thread(philosopher,id++,forkLock);
  }


  /**< Join the philosopher threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  return 0;
}

/* main.c ends here */
