QML Icons
=========

Use Material font icons (or other font icons like FontAwesome, fontello...) in QML.

Usage
-----

To use the icons in your project, follow these steps:

- Add qmlicons as a submodule to your project.

.. code:: console

    $ git submodule add https://github.com/stemoretti/qmlicons.git

- Include qmlicons.pri in your qmake project file.

.. code:: cmake

    include($$PATH_TO_QMLICONS/qmlicons.pri)

- In your C++ code, add the font to the application font database.

.. code:: cpp

    if (QFontDatabase::addApplicationFont(":/icons/MaterialIcons-Regular.ttf") == -1)
        qWarning() << "Failed to load font Material";

- Add the icon provider.
   
  Here you need to specify the image provider name and, in the
  IconProvider constructor, you must give the font family name and
  the json file that contains the conversion keys from the icons name
  to the characters code.

.. code:: cpp

    QQmlApplicationEngine engine;
    engine.addImageProvider("icon",
                            new IconProvider("Material Icons", ":/icons/codepoints.json"));

- Use the icons in any QML item that requires an image.

.. code:: qml

    ToolButton {
        icon.source: "image://icon/info"
        icon.color: Material.foreground
    }

    ItemDelegate {
        icon.source: "image://icon/settings"
        text: "Settings"
    }
