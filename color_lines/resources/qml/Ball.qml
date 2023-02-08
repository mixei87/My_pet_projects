import QtQuick 2.0

Rectangle {
    property color colorBall
    color: colorBall
    width: parent.width * 0.9
    height: parent.width * 0.9
    radius: parent.width
    anchors.centerIn: parent
}
