#include "iconprovider.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QPainter>

IconProvider::IconProvider(const QString &family, const QString &codesPath)
    : QQuickImageProvider(QQuickImageProvider::Image)
    , font(family)
{
    QFile file(codesPath);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        auto jd = QJsonDocument::fromJson(file.readAll());
        codepoints = jd.object();
    } else {
        qWarning() << "Cannot open icon codes file" << codesPath;
        qWarning() << file.errorString();
    }
}

QImage IconProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    int width = 48;
    int height = 48;

    if (requestedSize.width() > 0)
        width = requestedSize.width();

    if (requestedSize.height() > 0)
        height = requestedSize.height();

    if (size)
        *size = QSize(width, height);

    font.setPixelSize(width < height ? width : height);

    QImage image(width, height, QImage::Format_RGBA8888);
    image.fill(QColor(Qt::transparent));

    QString iconChar("?");
    if (codepoints.value(id).isUndefined())
        qWarning() << "Icon name" << id << "not found in" << font.family();
    else
        iconChar = codepoints[id].toString();

    QPainter painter(&image);
    painter.setFont(font);
    painter.drawText(0, height, iconChar);
    painter.end();

    return image;
}
