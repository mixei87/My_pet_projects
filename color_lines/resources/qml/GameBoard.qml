import QtQuick 2.0
import Game 1.0
import QtQuick.Controls
import QtQuick.Dialogs

GridView {
    id: root
    cellHeight: root.height / root.model.height_field
    cellWidth: root.width / root.model.width_field
    Dialog {
        id: dialogExit
        title: "GAME OVER"
        modal: true
        closePolicy: Popup.CloseOnEscape
        standardButtons: Dialog.OK | Dialog.Cansel
        width: parent.width * 0.7
        height: parent.height / 2
        anchors.centerIn: parent
        opacity: 0.98

        header: Label {
            text: dialogExit.title
            horizontalAlignment: Text.AlignHCenter
            color: "#ffffff"
            font.bold: true
            padding: 10
            background: Rectangle {
                color: "#707070"
                border.width: 1.0
                border.color: "#000000"
            }
        }

        contentItem: Label {
            text: qsTr("You result is excellent!\nAre you repeat?")
            font.pointSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "#ffffff"
            font.bold: true
            //        padding: 10
            background: Rectangle {
                color: "#353535"
            }
        }
        footer: DialogButtonBox {
            id: footerDialog
            background: Rectangle {
                color: "#353535"
            }
            height: 100
            anchors.fill: footerDialog
            Button {
                DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
                contentItem: Text {
                    text: qsTr("New Game")
                    color: "#ffffff"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 30
                }
                background: Rectangle {
                    color: "#8fbc8f"
                    radius: 10
                    border.width: 1.0
                    border.color: "#006400"
                }
            }
            Button {
                DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
                contentItem: Text {
                    text: qsTr("Quit")
                    color: "#ffffff"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 30
                }
                background: Rectangle {
                    color: "#cd5c5c"
                    radius: 10
                    border.width: 1.0
                    border.color: "#8b0000"
                }
            }
        }
        onAccepted: {
            root.model.newGame()
        }
        onRejected: {

            Qt.quit()
        }
    }
    delegate: Item {
        id: backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight
        Tile {
            id: tile
            anchors.fill: backgroundDelegate
            anchors.margins: backgroundDelegate.width * 0.03
            color: ((parseInt(
                         root.model.index / root.model.height_field) + root.model.index
                     % root.model.width_field) % 2) ? "#c0c0c0" : "#e3e3e3"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.model.moveBall(model.index)) {
                        if (!root.model.checkLines()) {
                            root.model.addRandomPoints()
                            //                                Qt.quit()
                        }
                    }
                    if (root.model.isGameOver()) {
                        dialogExit.open()
                        root.model.changeSelectedBalls(model.index)
                    }
                }
            }
            Ball {
                id: ball
                width: tile.width * 0.9
                height: tile.width * 0.9
                radius: tile.width
                anchors.centerIn: tile
                colorBall: model.display
                state: model.selectedBallRole
                visible: !Qt.colorEqual(model.display, "#000000")
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        root.model.changeSelectedBalls(model.index)
                        if (root.model.isGameOver()) {
                            dialogExit.open()
                            root.model.changeSelectedBalls(model.index)
                        }
                    }
                }

                states: [
                    State {
                        name: "clicked"
                        PropertyChanges {
                            target: ball
                        }
                    },
                    State {
                        name: ""
                        PropertyChanges {
                            target: ball
                            scale: 1.0
                        }
                    }
                ]
                transitions: [
                    Transition {
                        id: transition_pulse
                        from: "*"
                        to: "clicked"
                        SequentialAnimation {
                            id: pulseAnimation
                            loops: Animation.Infinite
                            NumberAnimation {
                                id: animationReduce
                                target: ball
                                properties: "scale"
                                to: 0.8
                                duration: 350
                            }
                            NumberAnimation {
                                id: animationIncrease
                                target: ball
                                properties: "scale"
                                to: 1.0
                                duration: 350
                            }
                        }
                    },
                    Transition {
                        from: "clicked"
                        to: "*"
                    }
                ]
            }
        }
    }
    GameController_qml {
        id: gameController
    }
    Component.onCompleted: {
        root.model = gameController.getModel()
    }
}
