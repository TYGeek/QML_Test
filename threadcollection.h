#ifndef THREADCOLLECTION_H
#define THREADCOLLECTION_H

#include <QObject>
#include <QtQml/qqmlregistration.h>


class ThreadProducer: public QObject
{
    Q_OBJECT
public:
    ThreadProducer(QObject* parent = 0);


public slots:
    void slotProcess();
    void slotStop();

private:
    int m_id;
    int m_value;
    bool m_stop;

signals:
    void signalValueChanged();
    void signalFinished();
};


class ThreadConsumer : public QObject
{
    Q_OBJECT
public:
    ThreadConsumer(QObject* parent = 0);

public slots:
    void slotPause();
    void slotProcess();
    void slotStop();


private:
    bool m_stop;
    bool m_pause;

signals:
    void signalReadySumm(int sum);
    void signalFinished();

};

#endif // THREADCOLLECTION_H
