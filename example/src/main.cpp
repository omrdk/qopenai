#include <QtPlugin>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QOpenAIAuthorization.h>

#ifdef Q_OS_IOS
#include "ImagePicker.h"
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    if(QOpenAIAuthorization::Authorizer().getKey().isEmpty()) {
        qDebug() << "Key not defined!";
        return EXIT_FAILURE;
    }

    #ifdef Q_OS_IOS
    qmlRegisterType<ImagePicker>("ImagePicker", 1, 0, "ImagePicker");
    #endif

    engine.load(QStringLiteral("qrc:/example/resources/qml/Main.qml"));

    if (engine.rootObjects().isEmpty()) {
        return EXIT_FAILURE;
    }

    return app.exec();
}
