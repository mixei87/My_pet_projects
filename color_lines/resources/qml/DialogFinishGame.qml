import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Dialogs

//Dialog {
//    id: root
//    title: "GAME OVER"
//    modal: true
//    closePolicy: Popup.CloseOnEscape
//    standardButtons: Dialog.OK | Dialog.Cansel
//    width: parent.width * 0.7
//    height: parent.height / 2
//    anchors.centerIn: parent
//    opacity: 0.98

//    header: Label {
//        text: root.title
//        horizontalAlignment: Text.AlignHCenter
//        color: "#ffffff"
//        font.bold: true
//        padding: 10
//        background: Rectangle {
//            color: "#707070"
//            border.width: 1.0
//            border.color: "#000000"
//        }
//    }

//    contentItem: Label {
//        text: qsTr("You result is excellent!\nAre you repeat?")
//        font.pointSize: 30
//        horizontalAlignment: Text.AlignHCenter
//        verticalAlignment: Text.AlignVCenter
//        color: "#ffffff"
//        font.bold: true
//        //        padding: 10
//        background: Rectangle {
//            color: "#353535"
//        }
//    }
//    footer: DialogButtonBox {
//        id: footerDialog
//        background: Rectangle {
//            color: "#353535"
//        }
//        height: 100
//        anchors.fill: footerDialog
//        Button {
//            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
//            contentItem: Text {
//                text: qsTr("New Game")
//                color: "#ffffff"
//                horizontalAlignment: Text.AlignHCenter
//                verticalAlignment: Text.AlignVCenter
//                font.pointSize: 30
//            }
//            background: Rectangle {
//                color: "#8fbc8f"
//                radius: 10
//                border.width: 1.0
//                border.color: "#006400"
//            }
//        }
//        Button {
//            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
//            contentItem: Text {
//                text: qsTr("Quit")
//                color: "#ffffff"
//                horizontalAlignment: Text.AlignHCenter
//                verticalAlignment: Text.AlignVCenter
//                font.pointSize: 30
//            }
//            background: Rectangle {
//                color: "#cd5c5c"
//                radius: 10
//                border.width: 1.0
//                border.color: "#8b0000"
//            }
//        }
//    }
//    onAccepted: {
//        GridView.model.newGame()
//    }
//    onRejected: {

//        Qt.quit()
//    }

//}
