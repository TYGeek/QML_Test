#include "threadcollection.h"
#include <QSemaphore>
#include <QMutex>
#include <QDebug>
#include <QThread>

static QMutex mutex;
static QSemaphore turnstile1(0);
static QSemaphore turnstile2(0);
static QSemaphore dataReady(0);
static int totalThreadProducer = 0;
static int curThreads = 0;
static int summ = 0;


ThreadProducer::ThreadProducer():
    m_id{10},
    m_value{0},
    m_stop{false}
{
    totalThreadProducer += 1;
}

void ThreadProducer::stopThread()
{
    QMutexLocker locker(&mutex);
    m_stop = true;
    emit finished();
}

void ThreadProducer::process()
{
    // Cycle body
    while(!m_stop)
    {

        mutex.lock();
            curThreads++;
            if (curThreads == totalThreadProducer)
                turnstile1.release(totalThreadProducer);  // unlock first turnstile
        mutex.unlock();

        turnstile1.acquire();   // first turnstile
         m_value++;

        mutex.lock();
        // critical section
        summ += m_value;
        mutex.unlock();

        mutex.lock();
            curThreads--;
            if (curThreads == 0)
            {
                dataReady.release();
            }
            mutex.unlock();

        turnstile2.acquire(); // second turnstile

        // stop thread if count to 100
        if ( m_value == 10 )
            stopThread();

    }
}


// --------------------------- ThreadConsumer ----------------------------
ThreadConsumer::ThreadConsumer():
    m_stop{false}
{

}

void ThreadConsumer::stopThread()
{
    QMutexLocker  locker(&mutex);
    m_stop = true;
    emit finished();
}

void ThreadConsumer::process()
{
    while(!m_stop)
    {
        dataReady.acquire();
        mutex.lock();

        QThread::sleep(1);
         emit newSum(summ);

         qDebug() << summ;

            summ = 0;
        mutex.unlock();
        turnstile2.release(totalThreadProducer); // unlock second turnstile
    }
}


