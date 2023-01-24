import QtQuick 2.0

GridView {
    id: root
    model: 81
    delegate: Tile {
        width: Math.min(root.width, root.height) / 9
        height: width
        //        Ball {
        //            id: ball
        //            width: tile.width * 0.8
        //            height: tile.width * 0.8
        //            radius: width
        //            anchors.centerIn: parent
        //        }
    }
}
