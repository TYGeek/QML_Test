#include "cppconnection.h"
#include <QDebug>
#include <QQmlComponent>
#include<QThread>
#include "threadcollection.h"


Controller::Controller(QObject *obj) : QObject{nullptr}

{

//        connect(counter_2, SIGNAL(finished()), consumer, SLOT(stopThread()));
}


void Controller::setValue(int value)
{
   current_value = value;
   emit valueChanged();
}

void Controller::start()
{
    if(consumer != nullptr)
       consumer = nullptr;
    consumer = new ThreadConsumer;
    if(counter_1 != nullptr)
       counter_1 = nullptr;
    counter_1 = new ThreadProducer;
    if(counter_2 != nullptr)
       counter_2 = nullptr;
    counter_2 = new ThreadProducer;
    //static ThreadProducer* counter_3 = new ThreadProducer;
    if(consumerThread != nullptr)
       consumerThread = nullptr;
    consumerThread = new QThread;
    if(counter_1Thread != nullptr)
       counter_1Thread = nullptr;
    counter_1Thread = new QThread;
    if(counter_2Thread != nullptr)
       counter_2Thread = nullptr;
    counter_2Thread = new QThread;

    connect(consumer, SIGNAL(newSum(int)), this, SLOT(setValue(int)));
    connect(counter_1, SIGNAL(finished()), consumer, SLOT(stopThread()));

    if(!consumerThread->isRunning())
    {
        consumer->moveToThread(consumerThread);
        connect(consumerThread, SIGNAL(started()), consumer, SLOT(process()));
        connect(consumer, SIGNAL(finished()), consumerThread, SLOT(quit()));
        connect(consumer, SIGNAL(finished()), consumer, SLOT(deleteLater()));
        connect(consumerThread, SIGNAL(finished()), consumerThread, SLOT(deleteLater()));
        consumerThread->start();
    }

    if(!counter_1Thread->isRunning())
    {
        counter_1->moveToThread(counter_1Thread);
        connect(counter_1Thread, SIGNAL(started()), counter_1, SLOT(process()));
        connect(counter_1, SIGNAL(finished()), counter_1Thread, SLOT(quit()));
        connect(counter_1, SIGNAL(finished()), counter_1, SLOT(deleteLater()));
        connect(counter_1Thread, SIGNAL(finished()), counter_1Thread, SLOT(deleteLater()));
        counter_1Thread->start();
    }

    if(!counter_2Thread->isRunning())
    {
        counter_2->moveToThread(counter_2Thread);
        connect(counter_2Thread, SIGNAL(started()), counter_2, SLOT(process()));
        connect(counter_2, SIGNAL(finished()), counter_2Thread, SLOT(quit()));
        connect(counter_2, SIGNAL(finished()), counter_2, SLOT(deleteLater()));
        connect(counter_2Thread, SIGNAL(finished()), counter_2Thread, SLOT(deleteLater()));
        counter_2Thread->start();
    }
}

int Controller::readValue()
{
    return current_value;
}



