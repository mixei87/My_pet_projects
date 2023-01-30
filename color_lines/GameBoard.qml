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
            color: ((parseInt(index / root.model.height_field) + index
                     % root.model.width_field) % 2) ? "#c0c0c0" : "#e3e3e3"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (root.model.getCurrentIndex() === -1) {
                        _pulseAnimation.running = true
                        console.log("1) index: ", index)
                        root.model.setCurrentIndex(index)
                    } else if (root.model.getCurrentIndex() === index) {
                        console.log("2) index: ", index)
                        console.log("   root.model.getCurrentIndex(): ",
                                    root.model.getCurrentIndex())
                        _pulseAnimation.running = false
                        ball.scale = 1
                        root.model.setCurrentIndex(-1)
                    } else {
                        console.log("3) index: ", index)
                        console.log("   root.model.getCurrentIndex(): ",
                                    root.model.getCurrentIndex())
                        var asd = root.model.getCurrentIndex()
                        _pulseAnimation(asd).running = false
                        root.model.setCurrentIndex(index)
                        asd = root.model.getCurrentIndex()
                        _pulseAnimation(asd).running = true
                    }

                    //                    root.model.swapPoints(index)
                }
            }
            Ball {
                id: ball
                width: tile.width * 0.9
                height: tile.width * 0.9
                radius: tile.width
                anchors.centerIn: tile
                colorBall: model.display
                visible: !Qt.colorEqual(model.display, "#000000")
                //                MouseArea {
                //                    anchors.fill: parent
                //                    onClicked: {

                //                    }
                //                }
                SequentialAnimation {
                    id: _pulseAnimation
                    //                    running: true
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
            }
        }
    }
} //ParallelAnimation {//    id: _animationAppear//    //                    NumberAnimation {//    //                        target: ball//    //                        property: "opacity"//    //                        from: 0.0//    //                        to: 1.0//    //                        duration: 500//    //                    }//    NumberAnimation {//        target: ball//        properties: "scale"//        //                        from: 0.0//        to: 0.8//        duration: 500//    }//}
