#ifndef CPPCONNECTION_H
#define CPPCONNECTION_H

#include <QtQml/qqmlregistration.h>
#include <QObject>
class QThread;
class ThreadConsumer;
class ThreadProducer;

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int value READ readValue WRITE setValue NOTIFY signalValueChanged);
    QML_ELEMENT
public:
    Controller(QObject *obj = 0);

    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void stop();

    ~Controller() override;
public slots:
    void setValue(int);

private:
    int readValue();
    int current_value;
    bool workStatus;
    ThreadConsumer* consumer;
    ThreadProducer* counter_1;
    ThreadProducer* counter_2;

    QThread* consumerThread;
    QThread* counter_1Thread;
    QThread* counter_2Thread;

signals:
    void signalValueChanged();
    void signalPause();
    void signalStop();
};

#endif // CPPCONNECTION_H
