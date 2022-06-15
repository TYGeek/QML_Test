#include "threadcollection.h"
#include <QSemaphore>
#include <QMutex>
#include <QDebug>
#include <QThread>
#include <QWaitCondition>


static QMutex mutex;
static QSemaphore turnstile1(0);
static QSemaphore turnstile2(0);
static QSemaphore dataReady(0);
static QSemaphore pauseConsumer(1);

static int totalThreadProducer = 0;
static int curThreads = 0;
static int summ = 0;


ThreadProducer::ThreadProducer(QObject* parent):
    m_id{10},
    m_value{0},
    m_stop{false}
{
    totalThreadProducer += 1;
}

void ThreadProducer::slotStop()
{
    QMutexLocker locker(&mutex);
    m_stop = true;
    emit signalFinished();
}

void ThreadProducer::slotProcess()
{
    m_stop = false;
    m_value = 0;
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
            slotStop();

    }
}


// --------------------------- ThreadConsumer ----------------------------
ThreadConsumer::ThreadConsumer(QObject* parent):
    m_stop{false},
    m_pause{false}
{

}

void ThreadConsumer::slotStop()
{
    QMutexLocker  locker(&mutex);
    m_stop = true;
    emit signalFinished();
}

void ThreadConsumer::slotPause()
{
    QMutexLocker locker(&mutex);

    if (m_pause)
    {
        pauseConsumer.release();
        m_pause = false;
    }
    else
    {
        pauseConsumer.acquire();
        m_pause = true;
    }
}

void ThreadConsumer::slotProcess()
{
    m_stop = false;
    while(!m_stop)
    {
        pauseConsumer.acquire();
        pauseConsumer.release();

        dataReady.acquire();
        mutex.lock();
            QThread::sleep(1);
            emit signalReadySumm(summ);
            qDebug() << summ;
            summ = 0;
        mutex.unlock();
        turnstile2.release(totalThreadProducer); // unlock second turnstile
    }
}


