import QtQuick
import QtQuick.Window
//import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Dialogs

Window {
    id: root
    width: 640
    height: 640
    visible: true
    title: qsTr("Color Lines")

    Component.onCompleted: {
        x = Screen.width * 2 / 3 - root.width / 3
        y = Screen.height / 2 - root.height / 2
    }

    GameBoard {
        anchors.centerIn: parent
        width: Math.min(root.width, root.height)
        height: width
    }
    //    Dialog {
    //        id: dialogNewGame
    //        title: "GAME OVER"
    //        standardButtons: Dialog.OK | Dialog.Cansel
    //        width: parent.width
    //        height: parent.height
    //    }

    //    Button {
    //        id: openFinishGameButton
    //        anchors.centerIn: parent
    //        text: "click me"
    //        onClicked: dialogFinishGame.open()
    //    }
}
