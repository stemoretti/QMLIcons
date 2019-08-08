#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QFontDatabase>
#include <QDebug>

#include "iconprovider.h"
#include "iconloader.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("com.github.stemoretti");
    QCoreApplication::setApplicationName("QmlIcons");

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    if (QFontDatabase::addApplicationFont(":/icons/MaterialIcons-Regular.ttf") == -1)
        qWarning() << "Failed to load font Material";

    QQuickStyle::setStyle("Fusion");

    QQmlApplicationEngine engine;

    IconLoader iconLoader(&engine);

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("iconLoader", &iconLoader);

    engine.addImageProvider("icon",
                            new IconProvider("Material Icons", ":/icons/codepoints.json"));

    iconLoader.loadIconFont("Material Icons", ":/icons/codepoints.json");

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
