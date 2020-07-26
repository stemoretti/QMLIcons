#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QObject>
#include <QQmlEngine>
#include <QFontDatabase>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QFile>

#include "../iconprovider.h"

class IconLoader : public QObject {
    Q_OBJECT

public:
    explicit IconLoader(QQmlEngine *engine, QObject *parent = nullptr)
        : QObject(parent)
        , m_engine(engine)
    {}

    Q_INVOKABLE
    void loadIconFont(const QString &fontFile, const QString &codepoints)
    {
        if (fontFile.isEmpty()) {
            qWarning() << "No font file specified";
            return;
        }

        int font_id = QFontDatabase::addApplicationFont(fontFile);
        if (font_id == -1) {
            qWarning() << "Failed to load font" << fontFile;
            return;
        }

        QStringList families = QFontDatabase::applicationFontFamilies(font_id);
        if (families.size() == 0) {
            qWarning() << "Unable to determine font families";
            return;
        }

        QFile file(codepoints);
        if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            auto jd = QJsonDocument::fromJson(file.readAll());
            if (!jd.isNull())
                m_codepoints = jd.object();
            else
                qWarning() << "Invalid codepoints JSON file" << codepoints;
        } else {
            qWarning() << "Cannot open icon codes file" << codepoints;
            qWarning() << file.errorString();
        }
        m_engine->addImageProvider("icon", new IconProvider(families[0], codepoints));
    }

    Q_INVOKABLE
    QStringList codepointsFiltered(const QString &filter = QString())
    {
        return m_codepoints.keys().filter(filter);
    }

private:
    QJsonObject m_codepoints;
    QQmlEngine *m_engine;
};

#endif
