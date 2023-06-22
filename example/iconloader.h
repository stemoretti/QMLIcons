#ifndef ICONLOADER_H
#define ICONLOADER_H

#include <QObject>
#include <QQmlEngine>
#include <QFontDatabase>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QFile>

#include <QtQml/qqmlregistration.h>

#include "iconprovider.h"

class IconLoader : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QString filter MEMBER m_filter NOTIFY filterChanged)
    Q_PROPERTY(QStringList codepointsFiltered READ codepointsFiltered NOTIFY codepointsFilteredChanged)

public:
    static IconLoader *create(QQmlEngine *engine, QJSEngine *)
    {
        return new IconLoader(engine);
    }

    Q_INVOKABLE
    bool loadIconFont(const QString &fontFile, const QString &codepoints)
    {
        if (fontFile.isEmpty()) {
            qWarning() << "No font file specified";
            return false;
        }

        int font_id = QFontDatabase::addApplicationFont(fontFile);
        if (font_id == -1) {
            qWarning() << "Failed to load font" << fontFile;
            return false;
        }

        QStringList families = QFontDatabase::applicationFontFamilies(font_id);
        if (families.size() == 0) {
            qWarning() << "Unable to determine font families";
            return false;
        }

        QFile file(codepoints);
        if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            auto jd = QJsonDocument::fromJson(file.readAll());
            if (jd.isNull()) {
                qWarning() << "Invalid codepoints JSON file" << codepoints;
                return false;
            } else {
                m_codepoints = jd.object();
            }
        } else {
            qWarning() << "Cannot open icon codes file" << codepoints;
            qWarning() << file.errorString();
            return false;
        }

        m_engine->addImageProvider("icon", new IconProvider(families[0], codepoints));
        updateFilterList();

        return true;
    }

    QStringList codepointsFiltered()
    {
        return m_codepointsFiltered;
    }

Q_SIGNALS:
    void filterChanged(const QString &filter);
    void codepointsFilteredChanged(const QStringList &keys);

private:
    explicit IconLoader(QQmlEngine *engine, QObject *parent = nullptr)
        : QObject(parent)
        , m_engine(engine)
    {
        connect(this, &IconLoader::filterChanged, this, &IconLoader::updateFilterList);
    }

    void updateFilterList()
    {
        m_codepointsFiltered = m_codepoints.keys().filter(m_filter);
        Q_EMIT codepointsFilteredChanged(m_codepointsFiltered);
    }

    QJsonObject m_codepoints;
    QQmlEngine *m_engine;
    QString m_filter;
    QStringList m_codepointsFiltered;
};

#endif
