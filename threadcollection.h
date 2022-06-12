#ifndef THREADCOLLECTION_H
#define THREADCOLLECTION_H

#include <QObject>
#include <QtQml/qqmlregistration.h>


class ThreadProducer: public QObject
{
    Q_OBJECT
public:
    ThreadProducer();
    void stopThread();
public slots:
    void process();

private:
    int m_id;
    int m_value;
    bool m_stop;

signals:
    void signalValueChanged();
    void finished();
};


class ThreadConsumer : public QObject
{
    Q_OBJECT
public:
    ThreadConsumer();

public slots:
    void process();
    void stopThread();

private:
    bool m_stop;

signals:
    void newSum(int sum);
    void finished();

};

#endif // THREADCOLLECTION_H
