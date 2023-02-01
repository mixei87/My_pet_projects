import QtQuick 2.0
import Game 1.0

GridView {
    id: root
    model: GameBoardModel {}
    cellHeight: root.height / root.model.height_field
    cellWidth: root.width / root.model.width_field
    delegate: Item {
        id: _backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight
        Tile {
            id: tile
            anchors.fill: _backgroundDelegate
            anchors.margins: _backgroundDelegate.width * 0.03
            color: ((parseInt(
                         model.index / root.model.height_field) + model.index
                     % root.model.width_field) % 2) ? "#c0c0c0" : "#e3e3e3"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.model.moveBall(model.index)) {
                        if (!root.model.checkLines()) {
                            root.model.addRandomPoints()
                        }
                    } else {

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
                selectedBall: model.display
                //                selectedBall: model.edit
                visible: !Qt.colorEqual(model.display, "#000000")
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
//                        if (root.model.getCurrentIndex() !== -1
//                                && root.model.getCurrentIndex(
//                                    ) !== model.index) {
//                            ball[root.model.getCurrentIndex()].state = ""
//                        }
                        root.model.setCurrentIndex(model.index)
                        ball.state === "clicked" ? ball.state = "" : ball.state = "clicked"
                    }
                }
                states: [
                    State {
                        name: "clicked"
                        PropertyChanges {
                            target: ball
                            selectedBall: true
                        }
                    },
                    State {
                        name: ""
                        PropertyChanges {
                            target: ball
                            scale: 1.0
                            selectedBall: false
                        }
                    }
                ]
                transitions: [
                    Transition {
                        id: _transition_pulse
                        from: ""
                        to: "clicked"
                        SequentialAnimation {
                            id: _pulseAnimation
                            loops: Animation.Infinite
                            NumberAnimation {
                                id: _animationReduce
                                target: ball
                                properties: "scale"
                                to: 0.8
                                duration: 500
                            }
                            NumberAnimation {
                                id: _animationIncrease
                                target: ball
                                properties: "scale"
                                to: 1.0
                                duration: 500
                            }
                        }
                    },
                    Transition {
                        from: "clicked"
                        to: ""
                    }
                ]
            }
        }
    }
}
