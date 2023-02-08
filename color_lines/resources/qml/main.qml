import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates

//import QtQuick.Dialogs
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
        text: gameBoard.model.record
        anchors.left: labelRecordGame.right
        anchors.verticalCenter: buttonNewGame.verticalCenter
        anchors.leftMargin: 20
    }

    LabelRecord {
        id: labelScoreGame
        text: "Score:"
        anchors.left: labelRecordGame.right
        anchors.verticalCenter: buttonNewGame.verticalCenter
        anchors.leftMargin: root.width / 4.5
    }

    LabelRecord {
        id: scoreGame
        text: gameBoard.model.score
        anchors.left: labelScoreGame.right
        anchors.verticalCenter: buttonNewGame.verticalCenter
        anchors.leftMargin: 20
    }

    GameBoard {
        id: gameBoard
        anchors.top: buttonNewGame.bottom
        anchors.left: parent.left
        anchors.margins: 10
        width: Math.min(root.width, root.height) - 20
        height: width
    }

    Component.onCompleted: {
        x = Screen.width * 2 / 3 - root.width / 3
        y = Screen.height / 2 - root.height / 2
    }
}
