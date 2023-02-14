import QtQuick 2.0
import Game 1.0
import QtQuick.Controls 2.15

GridView {
    id: root
    cellWidth: root.width / root.model.width_field
    cellHeight: root.height / root.model.height_field

    property int itemWidth: root.cellWidth
    property int itemHeight: root.cellHeight
    property int tileWidth: itemWidth
    property int tileHeight: itemHeight
    property int ballWidth: tileWidth * 0.9
    property int ballHeight: tileHeight * 0.9
    property int xfromBall: 0
    property int yfromBall: 0
    property int xtoBall: 0
    property int ytoBall: 0
    property bool busy: false

    delegate: Item {
        id: item
        width: itemWidth
        height: itemHeight

        Tile {
            id: tile
            anchors.fill: item
            anchors.margins: itemWidth * 0.03
            color: ((parseInt(
                         root.model.index / root.model.height_field) + root.model.index
                     % root.model.width_field) % 2) ? "#c0c0c0" : "#e3e3e3"
            Ball {
                id: ball
                anchors.centerIn: tile
                width: ballWidth
                height: ballHeight
                colorBall: model.display
                state: model.selectedBallRole
                visible: !Qt.colorEqual(model.display, "#000000")
                states: [
                    State {
                        name: ""
                    },
                    State {
                        name: "clicked"
                    },
                    State {
                        name: "appear"
                    },
                    State {
                        name: "disappear"
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
                        from: "clicked"
                        to: ""
                        NumberAnimation {
                            id: restoreAnimation
                            target: ball
                            properties: "scale"
                            to: 1
                        }
                    },
                    Transition {
                        from: "*"
                        to: "appear"
                        NumberAnimation {
                            id: appearScaleAnimation
                            target: ball
                            properties: "scale"
                            from: 0
                            to: 1
                            duration: 200
                        }
                    },
                    Transition {
                        from: "appear"
                        to: ""
                    },
                    Transition {
                        from: "*"
                        to: "disappear"
                        SequentialAnimation {
                            NumberAnimation {
                                id: bigScaleAnimation
                                target: ball
                                properties: "scale"
                                to: 1.1
                                duration: 200
                            }
                            NumberAnimation {
                                id: disappearScaleAnimation
                                target: ball
                                properties: "scale"
                                to: 0
                                duration: 200
                            }
                        }
                        onRunningChanged: {
                            if (!running) {
                                ball.scale = 1
                                root.model.setColor(index, "#000000")
                            }
                        }
                    },

                    Transition {
                        from: "disappear"
                        to: ""
                    }
                ]
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (!busy) {
                        if (root.model.changeSelectedBalls(model.index)) {
                            xtoBall = (item.width - ball.width) / 2 + item.x
                            ytoBall = (item.height - ball.height) / 2 + item.y
                            root.model.setGame_is_started(true)
                            animationBall.start()
                        } else {
                            xfromBall = (item.width - ball.width) / 2 + item.x
                            yfromBall = (item.height - ball.height) / 2 + item.y
                        }
                    }
                }
            }
        }
    }
    SequentialAnimation {
        id: animationBall
        ScriptAction {
            script: {
                busy = true
                var index = root.model.selectedIndex()
                var color = root.model.getColor(index)
                movedBall.color = color
                movedBall.visible = true
                root.model.setColor(index, "#000000")
                root.model.setState(index, "")
            }
        }
        ParallelAnimation {
            PropertyAnimation {
                target: movedBall
                properties: "x"
                from: xfromBall
                to: xtoBall
                easing.type: Easing.InOutBack
                duration: 400
            }
            PropertyAnimation {
                target: movedBall
                properties: "y"
                from: yfromBall
                to: ytoBall
                easing.type: Easing.InOutBack
                duration: 400
            }
        }
        ScriptAction {
            script: {
                var index = root.model.freeIndex()
                root.model.setColor(index, movedBall.color)
                movedBall.visible = false
                root.model.swapBalls()
                if (root.model.checkLines()) {
                    root.model.addRandomPoints()
                }
                if (root.model.isGameOver()) {
                    root.model.setRecord()
                    dialogFinishGame.visible = true
                }
                busy = false
            }
        }
    }
    Ball {
        id: movedBall
        width: ballWidth
        height: ballHeight
        visible: false
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
