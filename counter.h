#ifndef COUNTER_H
#define COUNTER_H

#include <QThread>
#include <QMutex>

class Counter: public QThread
{
    Q_OBJECT
public:
    Counter(int id, int value);
    void run() override;
    QMutex m_mutex;

private:
    int m_id;
    int m_value;

public slots:
    void pauseThread();
    void startThread();

signals:
    void signalThreadTick(int);

};

#endif // COUNTER_H
