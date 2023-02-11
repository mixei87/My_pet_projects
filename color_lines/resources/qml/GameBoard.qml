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
    property int xtoBall: 0
    property int ytoBall: 0

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
                Text {
                    text: model.selectedBallRole + model.index
                    color: "white"
                }

                //                visible: !Qt.colorEqual(model.display, "#000000")
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
                            x: root.model.xToBall()
                            y: root.model.yToBall()
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
                        SequentialAnimation {
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
                            ScriptAction {
                                script: ball.state = ""
                            }
                        }
                    },
                    Transition {
                        from: ""
                        to: "move"
                        SequentialAnimation {
                            ParentAnimation {
                                NumberAnimation {
                                    id: moveAnimation2
                                    target: ball
                                    properties: "x,y"
                                    duration: 1000
                                    easing.type: Easing.InOutBack
                                }
                            }
                            ScriptAction {
                                script: root.model.moveBall(model.index)
                            }
                            NumberAnimation {
                                id: moveAnimation3
                                target: ball
                                properties: "visible"
                                to: 0
                            }
                        }
                    }
                    //                    ,
                    //                    Transition {
                    //                        from: "move"
                    //                        to: ""
                    //                        SequentialAnimation {
                    //                            NumberAnimation {}
                    //                            ScriptAction {
                    //                                script: {
                    //                                    if (root.model.checkLines()) {
                    //                                        root.model.addRandomPoints()
                    //                                    }
                    //                                }
                    //                            }
                    //                        }
                    //                    }
                ]
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.model.changeSelectedBalls(model.index)) {
                        xtoBall = (item.width - ball.width) / 2 + item.x
                        ytoBall = (item.height - ball.height) / 2 + item.y
                        root.model.animationMoveBall(model.index)
                        ball.visible = false
                        animationBall.start()
                        root.model.moveBall(model.index)
                        //                        if (root.model.isGameOver()) {
                        //                            root.model.setRecord()
                        //                            dialogFinishGame.visible = true
                        //                        }
                    } else {
                        xfromBall = (item.width - ball.width) / 2 + item.x
                        yfromBall = (item.height - ball.height) / 2 + item.y
                    }
                }
            }
        }
    }
    SequentialAnimation {
        id: animationBall
        ParallelAnimation {
            ScriptAction {
                script: movedBall.visible = true
            }
            PropertyAnimation {
                target: movedBall
                properties: "x"
                from: xfromBall
                to: xtoBall
                easing.type: Easing.InOutBack
                duration: 600
            }
            PropertyAnimation {
                target: movedBall
                properties: "y"
                from: yfromBall
                to: ytoBall
                easing.type: Easing.InOutBack
                duration: 600
            }
            PropertyAnimation {
                target: ball
                properties: "colorBall"
                to: "brown"
            }
        }
        ScriptAction {
            script: movedBall.visible = false
        }
    }
    Ball {
        id: movedBall
        color: "grey"
        x: 0
        y: 0
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
