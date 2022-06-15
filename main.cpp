#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "cppconnection.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/visual/main.qml"_qs);//qrc:/main.qml

    QQmlComponent comp(&engine, url);

    QObject* pobj = comp.create();


    return app.exec();
}
