import QtQuick 2.0
import Game 1.0

GridView {
    id: root
    cellHeight: root.height / root.model.height_field
    cellWidth: root.width / root.model.width_field

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
                        }
                    }
                    if (root.model.isGameOver()) {
                        root.model.changeSelectedBalls(model.index)
                        root.model.setRecord()
                        dialogFinishGame.visible = true
                    }
                }
            }
            Ball {
                id: ball
                colorBall: model.display
                state: model.selectedBallRole
                visible: !Qt.colorEqual(model.display, "#000000")
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        root.model.changeSelectedBalls(model.index)
                        if (root.model.isGameOver()) {
                            root.model.setRecord()
                            dialogFinishGame.visible = true
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

    DialogFinishGame {
        id: dialogFinishGame
        onClicked: function (index) {
            if (index === 0) {
                Qt.quit()
            } else if (index === 1) {
                visible = false
                root.model.newGame()
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
