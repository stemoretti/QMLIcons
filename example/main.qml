import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Controls.Fusion
import QtQuick.Layouts
import QtQuick.Dialogs

import QmlIcons

ApplicationWindow {
    id: root

    visible: true
    title: "Qml Icons"
    width: 480
    height: 640

    palette: darkMode.checked ? darkTheme : lightTheme

    header: ToolBar {
        width: parent.width
        height: 50

        RowLayout {
            anchors.fill: parent

            Button {
                text: "Open font"
                onClicked: openFontWindow.show()
            }

            TextField {
                id: filter

                selectByMouse: true
                Layout.fillWidth: true
                placeholderText: "Filter"
                onTextChanged: IconLoader.filter = text
            }

            Label { text: "Size: " }

            SpinBox {
                id: fontSize

                implicitWidth: 60
                from: 6
                to: 100
                editable: true
                value: 50
            }

            CheckBox {
                id: darkMode

                text: "Dark Theme"
                checked: false
            }
        }
    }

    Palette {
         id: darkTheme

         alternateBase: "#353535"
         base: "#191919"
         brightText: "#ff0000"
         button: "#353535"
         buttonText: "#ffffff"
         highlight: "#2a82da"
         highlightedText: "#000000"
         light: "#808080"
         link: "#2a82da"
         placeholderText: "#80808080"
         text: "#ffffff"
         toolTipBase: "#2a82da"
         toolTipText: "#ffffff"
         window: "#353535"
         windowText: "#ffffff"

         active {
             button: "#252525"
         }

         disabled {
             buttonText: "#808080"
             text: "#808080"
             windowText: "#808080"
         }
     }

     Palette {
         id: lightTheme

         alternateBase: "#f7f7f7"
         base: "#ffffff"
         button: "#efefef"
         buttonText: "#000000"
         dark: "#9f9f9f"
         highlight: "#308cc6"
         highlightedText: "#ffffff"
         light: "#ffffff"
         mid: "#b8b8b8"
         midlight: "#cacaca"
         placeholderText: "#80000000"
         shadow: "#767676"
         text: "#000000"
         toolTipBase: "#ffffdc"
         toolTipText: "#000000"
         window: "#efefef"
         windowText: "#000000"

         disabled {
             base: "#efefef"
             buttonText: "#bebebe"
             dark: "#bebebe"
             highlight: "#919191"
             shadow: "#b1b1b1"
             text: "#bebebe"
             windowText: "#bebebe"
         }
     }

    Window {
        id: openFontWindow

        width: pane.implicitWidth
        height: pane.implicitHeight
        minimumWidth: pane.implicitWidth
        minimumHeight: pane.implicitHeight
        maximumWidth: width
        maximumHeight: height
        title: "Load Icon Font"
        flags: Qt.Dialog
        modality: Qt.ApplicationModal
        palette: root.palette

        FileDialog {
            id: fontFileDialog

            modality: Qt.ApplicationModal
            title: "Please choose a font file"
            onAccepted: iconFile.text = selectedFile.toString().substr(7)
        }

        FileDialog {
            id: jsonFileDialog

            modality: Qt.ApplicationModal
            title: "Please choose a json file"
            onAccepted: jsonFile.text = selectedFile.toString().substr(7)
        }

        Pane {
            id: pane

            anchors.fill: parent

            ColumnLayout {
                anchors.fill: parent

                GridLayout {
                    columns: 3

                    Label {
                        text: "Icon font file (ttf, otf):"
                        Layout.alignment: Qt.AlignRight
                    }

                    TextField {
                        id: iconFile

                        placeholderText: "No file selected"
                        readOnly: true
                        Layout.fillWidth: true
                    }

                    Button {
                        text: "..."
                        onClicked: fontFileDialog.open()
                        Layout.preferredWidth: 25
                    }

                    Label {
                        text: "Json codepoints file:"
                        Layout.alignment: Qt.AlignRight
                    }

                    TextField {
                        id: jsonFile

                        placeholderText: "No file selected"
                        readOnly: true
                        Layout.fillWidth: true
                    }

                    Button {
                        text: "..."
                        onClicked: jsonFileDialog.open()
                        Layout.preferredWidth: 25
                    }
                }

                RowLayout {
                    Layout.alignment: Qt.AlignHCenter

                    Button {
                        text: "Load"
                        enabled: iconFile.text.length > 0 && jsonFile.text.length > 0
                        onClicked: {
                            if (IconLoader.loadIconFont(iconFile.text, jsonFile.text))
                                openFontWindow.close()
                        }
                    }

                    Button {
                        text: "Cancel"
                        onClicked: openFontWindow.close()
                    }
                }
            }
        }
    }

    GridView {
        id: view

        anchors.fill: parent
        cellWidth: fontSize.value + 10
        cellHeight: cellWidth

        model: IconLoader.codepointsFiltered

        delegate: ToolButton {
            icon.width: fontSize.value
            icon.height: fontSize.value
            icon.source: "image://icon/" + modelData
            icon.color: palette.windowText
            hoverEnabled: true
            onClicked: console.log(modelData)

            ToolTip.delay: 1000
            ToolTip.timeout: 5000
            ToolTip.visible: hovered
            ToolTip.text: modelData
        }

        ScrollBar.vertical: ScrollBar { visible: true }
    }

    Component.onCompleted: {
        IconLoader.loadIconFont(":/QmlIcons/icons/MaterialIcons-Regular.ttf",
                                ":/QmlIcons/icons/codepoints.json");
    }
}
