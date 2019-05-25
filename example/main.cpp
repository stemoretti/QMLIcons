#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QFontDatabase>

#include "iconprovider.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    if (QFontDatabase::addApplicationFont(":/icons/MaterialIcons-Regular.ttf") == -1)
        qWarning() << "Failed to load font Material";

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    engine.addImageProvider("icon",
                            new IconProvider("Material Icons", ":/icons/codepoints.json"));

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
