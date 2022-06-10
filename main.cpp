#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include "cppconnection.h"
#include "calculation.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QQmlComponent comp(&engine, url);

    QObject* pobj = comp.create();

    CppConnection connection(pobj);


    return app.exec();
}
