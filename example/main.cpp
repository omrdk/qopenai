#include <QtPlugin>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#ifdef Q_OS_IOS
#include "ImagePicker.h"
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    if(qEnvironmentVariable("OPENAI_API_KEY").isEmpty()) {
        qDebug() << "OPENAI_API_KEY env var not defined!";
        return 1;
    }

    #ifdef Q_OS_IOS
    qmlRegisterType<ImagePicker>("ImagePicker", 1, 0, "ImagePicker");
    #endif

    engine.load(QStringLiteral("qrc:/example/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
