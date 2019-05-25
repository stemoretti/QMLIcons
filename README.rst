QML Icons
=========

Use Material font icons (or other font icons like FontAwesome, fontello...) in QML.

Usage
-----

To use the icons in your project, follow these steps:

1. Either include qmlicons.pri in your project file or
   copy iconprovider.(h|cpp) and the directory "icons" in your project.

2. Add the font to the application font database.

.. code:: cpp

    #include <QFontDatabase>

    ...

    if (QFontDatabase::addApplicationFont(":/icons/MaterialIcons-Regular.ttf") == -1)
        qWarning() << "Failed to load font Material";

3. Add the icon provider.
   
   Here you need to specify the image provider name and, in the
   IconProvider constructor, you must give the font family name and
   the json file that contains the conversion keys from the icons name
   to the characters code.

.. code:: cpp

    #include <QQmlApplicationEngine>

    ...

    QQmlApplicationEngine engine;
    engine.addImageProvider("icon",
                            new IconProvider("Material Icons", ":/icons/codepoints.json"));

4. You can use the icons in any item that requires an image.

.. code:: qml

    import QtQuick 2.12

    ...

    ToolButton {
        icon.source: "image://icon/info"
    }

    ...

    ItemDelegate {
        icon.source: "image://icon/settings"
        text: "Settings"
    }
