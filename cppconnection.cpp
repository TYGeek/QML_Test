#include "cppconnection.h"
#include <QDebug>
#include <QQmlComponent>
#include <QThread>
#include "threadcollection.h"


Controller::Controller(QObject *obj) : QObject{nullptr}
{

    consumer = new ThreadConsumer;
    counter_1 = new ThreadProducer;
    counter_2 = new ThreadProducer;

    consumerThread = new QThread(this);
    counter_1Thread = new QThread(this);
    counter_2Thread = new QThread(this);

    consumer->moveToThread(consumerThread);
    counter_1->moveToThread(counter_1Thread);
    counter_2->moveToThread(counter_2Thread);


    // stop connection
    QObject::connect(this,      &Controller::signalStop,
                     consumer,  &ThreadConsumer::slotStop);
    QObject::connect(this,      &Controller::signalStop,
                     counter_1, &ThreadProducer::slotStop);
    QObject::connect(this,      &Controller::signalStop,
                     counter_2, &ThreadProducer::slotStop);
    // pause connection
    QObject::connect(this,      &Controller::signalPause,
                     consumer,  &ThreadConsumer::slotPause);


    // set consumer <-> controller connection
    QObject::connect(consumer,  &ThreadConsumer::signalReadySumm,
                     this,      &Controller::setValue);

    // set consumer <-> thread connecion
    QObject::connect(consumerThread, &QThread::started,
                     consumer,       &ThreadConsumer::slotProcess);

    QObject::connect(consumer,       &ThreadConsumer::signalFinished,
                     consumerThread, &QThread::quit);

//    QObject::connect(consumer, &ThreadConsumer::signalFinished,
//                     consumer, &ThreadConsumer::deleteLater);

//    QObject::connect(consumerThread, &QThread::finished,
//                     consumerThread, &QThread::deleteLater);

    // set counter_1 <-> thread connecion
    QObject::connect(counter_1Thread,    &QThread::started,
                     counter_1,          &ThreadProducer::slotProcess);

    QObject::connect(counter_1,          &ThreadProducer::signalFinished,
                     counter_1Thread,    &QThread::quit);

//    QObject::connect(counter_1, &ThreadProducer::signalFinished,
//                     counter_1, &ThreadProducer::deleteLater);

//    QObject::connect(counter_1Thread, &QThread::finished,
//                     counter_1Thread, &QThread::deleteLater);

    // set counter_2 <-> thread connecion
    QObject::connect(counter_2Thread,    &QThread::started,
                     counter_2,          &ThreadProducer::slotProcess);

    QObject::connect(counter_2,          &ThreadProducer::signalFinished,
                     counter_2Thread,    &QThread::quit);

//    QObject::connect(counter_2, &ThreadProducer::signalFinished,
//                     counter_2, &ThreadProducer::deleteLater);

//    QObject::connect(counter_2Thread, &QThread::finished,
//                     counter_2Thread, &QThread::deleteLater);

}

void Controller::setValue(int value)
{
   current_value = value;
   emit signalValueChanged();
}

void Controller::start()
{
    consumerThread->start();
    counter_1Thread->start();
    counter_2Thread->start();
}

void Controller::pause()
{
    consumer->slotPause();

    //emit signalPause();
}

void Controller::stop()
{
    consumer->slotStop();
    counter_1->slotStop();
    counter_2->slotStop();

    //emit signalStop();
}

int Controller::readValue()
{
    return current_value;
}

Controller::~Controller()
{
    consumer->deleteLater();
    counter_1->deleteLater();
    counter_2->deleteLater();

    consumerThread->quit();
    consumerThread->deleteLater();

    counter_1Thread->quit();
    counter_1Thread->deleteLater();

    counter_2Thread->quit();
    counter_2Thread->deleteLater();
}
