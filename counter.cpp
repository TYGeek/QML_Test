#include "counter.h"
#include<QThread>
#include<QCoreApplication>
Counter::Counter(int id, int value, QObject* ptr):QObject{ptr},
    m_id{id},
    m_value{value}
{

}

void Counter::doCount()
{
   while(m_value < 100000)
    {
        m_mutex.lock();
        m_value += 1;
        emit signalThreadTick(m_value);
        m_mutex.unlock();
    }
   if(m_value > 100000)
   {
       emit finished();
   }


}

//void Counter::pauseThread()
//{
////    if( !m_mutex.tryLock() )
////       m_mutex.lock();
//}

//void Counter::continueThread()
//{
////    if(m_mutex.tryLock())
////        m_mutex.unlock();
//}


