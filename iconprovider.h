#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QQuickImageProvider>
#include <QJsonObject>
#include <QFont>

class IconProvider : public QQuickImageProvider
{
public:
    explicit IconProvider(const QString &family, const QString &codesPath);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
private:
    QJsonObject codepoints;
    QFont font;
};

#endif // ICONPROVIDER_H
