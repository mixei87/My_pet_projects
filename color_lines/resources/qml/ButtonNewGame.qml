import QtQuick 2.0
import QtQuick.Templates 2.15

Button {
    id: root
    width: parent.width / 5
    height: 0.06 * parent.height
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.margins: 10
    Text {
        id: textNewGame
        anchors.centerIn: parent
        text: "New game"
        color: "#FCFCFC"
        font {
            pointSize: 18
            bold: true
        }
    }
    background: Rectangle {
        color: root.pressed ? "#3ca371" : "#3cb371"
        opacity: root.hovered ? 0.8 : 1
        radius: 8
    }
    onClicked: {
        gameBoard.model.setRecord()
        gameBoard.model.newGame()
        recordGame.text = gameBoard.model.record
        scoreGame.text = gameBoard.model.score
    }
}
