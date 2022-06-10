#ifndef CPPCONNECTION_H
#define CPPCONNECTION_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include "counter.h"


class CppConnection : public QObject
{
    Q_OBJECT
public:
    explicit CppConnection(QObject *obj);


public slots:
    void slotDraw(int);

private:
    QObject* m_pObj;
    std::unique_ptr<Counter> m_pThreadCounter_1;

    int m_numThreadReady;
};

#endif // CPPCONNECTION_H
