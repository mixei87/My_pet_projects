import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: root
    width: 750
    height: 810
    minimumWidth: 500
    minimumHeight: 500
    visible: true
    title: qsTr("Color Lines")

    ButtonNewGame {
        id: buttonNewGame
    }

    LabelRecord {
        id: labelRecordGame
        text: "Record:"
        anchors.left: buttonNewGame.right
        anchors.verticalCenter: buttonNewGame.verticalCenter
        anchors.leftMargin: root.width / 10
    }
    LabelRecord {
        id: recordGame
        record: gameBoard.model.record + state
        anchors.left: labelRecordGame.right
        anchors.verticalCenter: buttonNewGame.verticalCenter
        anchors.leftMargin: 20
        Behavior on record {
            SequentialAnimation {
                NumberAnimation {
                    target: recordGame
                    properties: "scale"
                    to: 1.3
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: recordGame
                    properties: "scale"
                    to: 1
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    LabelScore {
        id: labelScoreGame
        text: "Score:"
        anchors.left: labelRecordGame.right
        anchors.verticalCenter: buttonNewGame.verticalCenter
        anchors.leftMargin: root.width / 4.5
    }

    LabelScore {
        id: scoreGame
        score: gameBoard.model.score
        anchors.left: labelScoreGame.right
        anchors.verticalCenter: buttonNewGame.verticalCenter
        anchors.leftMargin: 20
        Behavior on score {
            SequentialAnimation {
                NumberAnimation {
                    target: scoreGame
                    properties: "scale"
                    to: 1.2
                    duration: 100
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: scoreGame
                    properties: "scale"
                    to: 1
                    duration: 100
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    GameBoard {
        id: gameBoard
        anchors.top: buttonNewGame.bottom
        anchors.left: parent.left
        anchors.margins: 10
        width: Math.min(root.width, root.height) - 20
        height: width
        interactive: false
    }

    Component.onCompleted: {
        x = Screen.width / 2 - root.width / 2
        y = Screen.height / 2 - root.height / 2
    }
}
