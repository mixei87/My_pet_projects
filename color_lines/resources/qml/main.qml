import QtQuick 2.15

Window {
    id: root
    width: 750
    height: 810
    minimumWidth: 500
    minimumHeight: 500
    visible: true
    title: qsTr("Color Lines")

    //    Item {
    //        width: 200
    //        height: 100

    //        Rectangle {
    //            id: redRect
    //            width: 100
    //            height: 100
    //            color: "red"
    //        }

    //        Rectangle {
    //            id: blueRect
    //            x: redRect.width
    //            width: 50
    //            height: 50
    //            color: "blue"

    //            states: State {
    //                name: "reparented"
    //                ParentChange {
    //                    target: blueRect
    //                    parent: redRect
    //                    x: 10
    //                    y: 10
    //                }
    //            }

    //            transitions: Transition {
    //                ParentAnimation {
    //                    NumberAnimation {
    //                        properties: "x,y"
    //                        duration: 1000
    //                    }
    //                }
    //            }

    //            MouseArea {
    //                anchors.fill: parent
    //                onClicked: blueRect.state = "reparented"
    //            }
    //        }
    //    }
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
        score: gameBoard.model.record
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
        score: gameBoard.model.score
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
    //    Rectangle {
    //        id: movingBall
    //        radius: parent.width
    //        Text {
    //            text: gameBoard.objectName
    //        }
    //        width: 100 //gameBoard.children[0].width
    //        height: width

    //        //        color: "green"
    //        x: 100 //gameBoard.model.xSelectedBall()
    //        y: 100
    //        visible: true
    //        MouseArea {
    //            anchors.fill: parent
    //            onClicked: {
    //                console.log("move click, state =", state)
    //                state = "move"
    //                console.log("move click2, state =", state)
    //                console.log("gameBoard.model.xSelectedBall() =",
    //                            gameBoard.model.xSelectedBall())
    //            }
    //        }

    //        states: [
    //            State {
    //                name: ""
    //                PropertyChanges {
    //                    target: movingBall
    //                    x: gameBoard.model.xSelectedBall()
    //                }
    //            },
    //            State {
    //                name: "move"
    //                PropertyChanges {
    //                    target: movingBall
    //                    x: gameBoard.model.xSelectedBall()
    //                }
    //            }
    //        ]
    //        transitions: [
    //            Transition {
    //                from: "*"
    //                to: "move"
    //                NumberAnimation {
    //                    id: animation333
    //                    target: movingBall
    //                    properties: "x"
    //                    duration: 1000
    //                    easing.type: Easing.InOutBack
    //                }
    //                onRunningChanged: {
    //                    if (!running)
    //                        state = ""
    //                }
    //            }
    //        ]
    //    }
    Component.onCompleted: {
        x = Screen.width * 2 / 3 - root.width / 8
        y = Screen.height / 2 - root.height / 2
    }
}
