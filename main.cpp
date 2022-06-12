#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "cppconnection.h"
#include "calculation.h"


int main(int argc, char *argv[])
{
//#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/visual/main.qml"_qs);//qrc:/main.qml

    QQmlComponent comp(&engine, url);

    QObject* pobj = comp.create();
 //   qDebug() << comp.errors();
//    Controller connection;
//    connection.setHandler(pobj);
//    connection.setConnections();


    return app.exec();
}
