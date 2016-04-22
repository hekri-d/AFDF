#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QtQml>

#include "arrayfromdata.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ArrayFromData>("ArrayFromData",1,0,"ArrayFromData");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));





    return app.exec();
}
