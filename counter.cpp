#include "counter.h"

Counter::Counter(int id, int value):
    m_id{id},
    m_value{value}
{

}

void Counter::run()
{
    for(int i = 0; i < 10; ++i)
    {
        m_mutex.lock();

        usleep(1000000);
        m_value = i;
        emit signalThreadTick(m_value);

        m_mutex.unlock();
    }

}

void Counter::pauseThread()
{
    if( !m_mutex.tryLock() )
        m_mutex.lock();
}

void Counter::startThread()
{
   if (!isRunning())
       start();
   else
       m_mutex.unlock();

}
