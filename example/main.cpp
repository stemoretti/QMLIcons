#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include "iconloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("com.github.stemoretti");
    QCoreApplication::setApplicationName("QmlIcons");

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QQuickStyle::setStyle("Fusion");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    IconLoader iconLoader(&engine);
    iconLoader.loadIconFont(":/icons/MaterialIcons-Regular.ttf",
                            ":/icons/codepoints.json");

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("iconLoader", &iconLoader);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
