/**
 * @file Semaphore.h
 * @author Liam Durkan (C00264405)
 * @date 07/10/2023
 * @copyright GPL-3.0
 */

#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <mutex>
#include <condition_variable>

/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/
class Semaphore
{
private:
    unsigned int m_uiCount; /*!< Holds the Semaphore count */
    std::mutex m_mutex;
    std::condition_variable m_condition;

public:
    Semaphore(unsigned int uiCount=0)
      : m_uiCount(uiCount) { };
    void Wait();
    void Signal();

};


// Your Semaphore class code here

#endif // SEMAPHORE_H