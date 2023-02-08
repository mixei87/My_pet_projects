import QtQuick 2.0
import QtQuick.Controls 2.15

Rectangle {
    id: root
    property string text
    property variant buttons

    signal clicked(int index)

    width: parent.width * 0.7
    height: parent.height / 2
    anchors.centerIn: parent
    color: "#353535"
    radius: root.height * 0.03
    opacity: 0.97
    visible: false
    text: 'You result is excellent!\nAre you repeat?'
    buttons: ['Quit', 'New Game']

    Text {
        text: root.text
        anchors {
            centerIn: parent
            verticalCenterOffset: -0.1 * root.height
        }
        color: "white"
        font.pixelSize: 0.1 * root.height
        width: 0.9 * parent.width
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }
    Row {
        id: row
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
            bottomMargin: 0.1 * root.height
        }
        spacing: 0.03 * root.width
        Repeater {
            id: repeater
            model: buttons
            delegate: Button {
                width: Math.min(
                           0.5 * root.width,
                           (0.9 * root.width - (repeater.count - 1) * row.spacing) / repeater.count)
                height: 0.2 * root.height
                text: modelData
                font {
                    pixelSize: 0.35 * row.height
                    bold: true
                }
                background: Rectangle {
                    color: index === 0 ? "#cd5c5c" : "#3cb371"
                    radius: 8
                }
                onClicked: root.clicked(index)
            }
        }
    }
}
