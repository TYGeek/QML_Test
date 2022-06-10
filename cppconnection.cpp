#include "cppconnection.h"
#include <QDebug>
#include <QQmlComponent>



CppConnection::CppConnection(QObject *obj)
    : QObject{nullptr},
      m_pObj{obj},
      m_pThreadCounter_1( std::make_unique<Counter>( 0, 0 ))

{

    // set connection with button start
    QObject* pBtnStart = m_pObj->findChild<QObject*>("btnStart");
    if (pBtnStart)
    {
        QObject::connect(pBtnStart,                 SIGNAL( clicked() ),
                         m_pThreadCounter_1.get(),  SLOT( startThread() )
                         );

        QObject::connect(m_pThreadCounter_1.get(),  SIGNAL( signalThreadTick(int) ),
                         this,                      SLOT ( slotDraw(int) )
                         );
    }

    // set connection with button pause
    QObject* pBtnPause = m_pObj->findChild<QObject*>("btnPause");
    if (pBtnPause)
    {
        QObject::connect(pBtnPause,                 SIGNAL( clicked() ),
                         m_pThreadCounter_1.get(),  SLOT ( pauseThread() )
                         );

    }

}


void CppConnection::slotDraw(int value)
{
    QObject* pText = m_pObj->findChild<QObject*>("textObj");
    if( pText )
    {
        pText->setProperty("text", QString::number(value));
    }
}

