import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts

Window {
    id: root
    width: 640
    height: 640
    visible: true
    title: qsTr("Color Lines")

    Component.onCompleted: {
        x = Screen.width * 2 / 3 - root.width / 3
        y = Screen.height / 2 - root.height / 2
    }

    GameBoard {
        anchors.centerIn: parent
        width: Math.min(root.width, root.height)
        height: width
    }
}
