#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include "timer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // @uri TimerModule
    qmlRegisterType<TimerModule>("TimerModule", 1, 0, "TimerModule");

    // Main: Widgets Manage.
    QQmlApplicationEngine main;
    QObject::connect(
        &main,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    main.loadFromModule("Modular", "MainWindow");

    if(!main.rootObjects().isEmpty()) {
        QObject *root = main.rootObjects().at(0);
        auto window = qobject_cast<QQuickWindow*>(root);
        if (window) {
            Qt::WindowFlags flags = window->flags();
            window->setFlags(flags);

            window->show();
        }
    }

    return app.exec();
}
