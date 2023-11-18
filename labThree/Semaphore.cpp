/**
 * @file Semaphore.cpp
 * @author Liam Durkan (C00264405)
 * @date 07/10/2023
 * @copyright GPL-3.0
 */


#include "Semaphore.h"
/*! \class Semaphore
    \brief A Semaphore Implementation

   Uses C++11 features such as mutex and condition variables to implement Semaphore

*/


/*! closes thread */ 
void Semaphore::Wait()
{
      std::unique_lock< std::mutex > lock(m_mutex);
      m_condition.wait(lock,[&]()->bool{ return m_uiCount>0; });
      --m_uiCount; 
}


/*! allows a thread to open */
void Semaphore::Signal() 
{
      std::unique_lock< std::mutex > lock(m_mutex);
      ++m_uiCount;
      m_condition.notify_one();
}
