import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Color Lines")

    Component.onCompleted: {
        x = Screen.width / 2 - root.width / 2
        y = Screen.height / 2 - root.height / 2
    }
    GameBoard {
        anchors.fill: parent
    }
}
