#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("com.github.stemoretti");
    QCoreApplication::setApplicationName("QmlIcons");

    QQuickStyle::setStyle("Fusion");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
