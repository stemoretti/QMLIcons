import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3

ApplicationWindow {
    id: appWindow

    visible: true
    title: "Qml Icons"
    width: 360
    height: 480

    header: ToolBar {
        width: parent.width
        height: 50
        RowLayout {
            anchors.fill: parent
            Button {
                text: "Open font"
                onClicked: openFontWindow.show()
            }

            Text { text: "Filter: " }
            TextField {
                id: filter
                selectByMouse: true
                Layout.fillWidth: true
                onTextChanged: view.model = iconLoader.codepointsFiltered(text)
            }

            Text { text: "Font size: " }
            SpinBox {
                id: fontSize
                implicitWidth: 60
                from: 6
                to: 100
                editable: true
                value: 50
            }
        }
    }

    FileDialog {
        id: fileDialog

        property var actionFunc

        folder: shortcuts.home
        onAccepted: actionFunc(fileUrl.toString().substr(7))
    }

    Window {
        id: openFontWindow

        width: 200
        height: column.implicitHeight
        title: "Load Icon Font"
        flags: Qt.Dialog

        ColumnLayout {
            id: column
            anchors.fill: parent

            Text { text: "Icon font file (ttf, otf):" }
            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: iconFile
                    selectByMouse: true
                    Layout.fillWidth: true
                }
                Button {
                    text: "Choose..."
                    onClicked: {
                        fileDialog.title = "Please choose a font file"
                        fileDialog.actionFunc = function (file) {
                            iconFile.text = file
                        }
                        fileDialog.open()
                    }
                }
            }

            Text { text: "Json codepoints file:" }
            RowLayout {
                Layout.fillWidth: true
                TextField {
                    id: jsonFile
                    selectByMouse: true
                    Layout.fillWidth: true
                }
                Button {
                    text: "Choose..."
                    onClicked: {
                        fileDialog.title = "Please choose a json file"
                        fileDialog.actionFunc = function (file) {
                            jsonFile.text = file
                        }
                        fileDialog.open()
                    }
                }
            }

            Item { Layout.fillHeight: true }

            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                Button {
                    text: "Load"
                    onClicked: {
                        if (iconFile.text.length > 0 && jsonFile.text.length > 0) {
                            iconLoader.loadIconFont(iconFile.text, jsonFile.text)
                            view.model = iconLoader.codepointsFiltered(filter.text)
                            openFontWindow.close()
                        }
                    }
                }
                Button {
                    text: "Cancel"
                    onClicked: openFontWindow.close()
                }
            }
        }
    }

    GridView {
        id: view

        anchors.fill: parent
        cellWidth: fontSize.value + 10
        cellHeight: cellWidth

        model: iconLoader.codepointsFiltered()

        delegate: ToolButton {
            icon.width: fontSize.value
            icon.height: fontSize.value
            icon.source: "image://icon/" + modelData
            hoverEnabled: true
            onClicked: console.log(modelData)

            ToolTip.delay: 1000
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            ToolTip.text: modelData
        }
    }
}
