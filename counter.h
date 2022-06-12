#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QMutex>

class Counter: public QObject
{
    Q_OBJECT
public:
    Counter(int id, int value, QObject* ptr = 0);

    QMutex m_mutex;

private:
    int m_id;
    int m_value;

public slots:
//    void pauseThread();
//    void continueThread();
    void doCount();
signals:
    void signalThreadTick(int);
    void finished();
};

#endif // COUNTER_H
