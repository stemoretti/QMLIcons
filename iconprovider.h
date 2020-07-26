#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QQuickImageProvider>
#include <QFont>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPainter>
#include <QFontMetrics>

class IconProvider : public QQuickImageProvider
{
public:
    explicit IconProvider(const QString &family, const QString &codesPath)
        : QQuickImageProvider(QQuickImageProvider::Image)
        , font(family)
    {
        QFile file(codesPath);
        if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            auto jd = QJsonDocument::fromJson(file.readAll());
            if (!jd.isNull())
                codepoints = jd.object();
            else
                qWarning() << "Invalid codepoints JSON file" << codesPath;
        } else {
            qWarning() << "Cannot open icon codes file" << codesPath;
            qWarning() << file.errorString();
        }
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override
    {
        int width = 48;
        int height = 48;

        if (requestedSize.width() > 0)
            width = requestedSize.width();

        if (requestedSize.height() > 0)
            height = requestedSize.height();

        if (size)
            *size = QSize(width, height);

        QString iconChar("?");
        if (codepoints.value(id).isUndefined())
            qWarning() << "Icon name" << id << "not found in" << font.family();
        else
            iconChar = codepoints[id].toString();

        font.setPixelSize(width < height ? width : height);

        QFontMetrics fm(font);
        double widthRatio = double(width) / fm.boundingRect(iconChar).width();
        if (widthRatio < 1.0)
            font.setPixelSize(font.pixelSize() * widthRatio);

        QImage image(width, height, QImage::Format_RGBA8888);
        image.fill(Qt::transparent);

        QPainter painter(&image);
        painter.setFont(font);
        painter.drawText(QRect(0, 0, width, height), Qt::AlignCenter, iconChar);

        return image;
    }

private:
    QJsonObject codepoints;
    QFont font;
};

#endif // ICONPROVIDER_H
