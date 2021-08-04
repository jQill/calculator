#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "calcmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<CalcModel>("Calc", 1, 0, "CalcModel");

    CalcModel calc;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("calcModel", &calc);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
