import QtQuick 2.0
import Game 1.0
import QtQuick.Controls 2.15

GridView {
    id: root
    cellHeight: root.height / root.model.height_field
    cellWidth: root.width / root.model.width_field
    delegate: Item {

        id: item
        width: root.cellWidth
        height: root.cellHeight
        Tile {
            id: tile
            anchors.fill: item
            anchors.margins: item.width * 0.03
            color: ((parseInt(
                         root.model.index / root.model.height_field) + root.model.index
                     % root.model.width_field) % 2) ? "#c0c0c0" : "#e3e3e3"

            Ball {

                id: ball
                width: tile.width * 0.9
                height: tile.width * 0.9
                anchors.centerIn: tile
                //                anchors.centerIn: parent
                colorBall: model.display
                state: model.selectedBallRole
                visible: !Qt.colorEqual(model.display, "#000000")
                //                Behavior on x {
                //                    NumberAnimation {
                //                        duration: 400
                //                        easing.type: Easing.InOutCubic
                //                    }
                //                }
                states: [
                    State {
                        name: ""
                        PropertyChanges {
                            target: ball
                            scale: 1
                        }
                    },
                    State {
                        name: "clicked"
                    },
                    State {
                        name: "appear"
                    },
                    State {
                        name: "move"

                        ParentChange {
                            target: ball
                            parent: root
                            x: root.model.xSelectedBall()
                            y: root.model.ySelectedBall()
                            scale: 1
                        }
                    }
                ]

                transitions: [
                    Transition {
                        id: transition_pulse
                        from: ""
                        to: "clicked"
                        SequentialAnimation {
                            id: pulseAnimation
                            loops: Animation.Infinite
                            NumberAnimation {
                                id: reduceAnimation
                                target: ball
                                properties: "scale"
                                to: 0.8
                                duration: 350
                            }
                            NumberAnimation {
                                id: increaseAnimation
                                target: ball
                                properties: "scale"
                                to: 1
                                duration: 350
                            }
                        }
                    },
                    Transition {
                        from: ""
                        to: "appear"
                        ParallelAnimation {
                            id: appearAnimation
                            NumberAnimation {
                                id: appearOpacityAnimation
                                target: ball
                                properties: "opacity"
                                from: 0
                                to: 1
                                duration: 150
                            }
                            NumberAnimation {
                                id: appearScaleAnimation
                                target: ball
                                properties: "scale"
                                from: 0
                                to: 1
                                duration: 200
                            }
                        }
                        onRunningChanged: {
                            if (!running)
                                ball.state = ""
                        }
                    },
                    Transition {
                        from: "*"
                        to: "move"
                        ParentAnimation {
                            NumberAnimation {
                                id: moveAnimation2
                                target: ball
                                properties: "x,y"
                                duration: 1000
                                easing.type: Easing.InOutBack
                            }
                        }
                    }
                ]
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.model.changeSelectedBalls(
                                model.index,
                                (item.width - ball.width) / 2 + item.x,
                                (item.height - ball.height) / 2 + item.y)) {

                        root.model.moveBall(model.index)
                        if (root.model.checkLines()) {

                            root.model.addRandomPoints()
                        }
                        if (root.model.isGameOver()) {
                            root.model.setRecord()
                            dialogFinishGame.visible = true
                        }
                    }
                }
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
