import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: appWindow

    visible: true
    title: "Qml Icons"
    width: 360
    height: 480

    GridView {
        id: view
        anchors.fill: parent
        cellWidth: width / 6
        cellHeight: cellWidth

        delegate: ItemDelegate {
            icon.source: "image://icon/" + modelData
            onClicked: console.log(modelData)
        }
    }

    Component.onCompleted: {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.HEADERS_RECEIVED) {
                print('HEADERS_RECEIVED')
            } else if(xhr.readyState === XMLHttpRequest.DONE) {
                print('DONE')
                var obj = JSON.parse(xhr.responseText.toString());
                var keys = []

                for (var k in obj)
                    keys.push(k)

                view.model = keys
            }
        }
        xhr.open("GET", "qrc:icons/codepoints.json");
        xhr.send();
    }
}
