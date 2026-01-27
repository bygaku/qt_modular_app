#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Main: Widgets Manage.
    QQmlApplicationEngine main;

    QObject::connect(
        &main,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    main.loadFromModule("Modular", "MainWindow");

    if(main.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
