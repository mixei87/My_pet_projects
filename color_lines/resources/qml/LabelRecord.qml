import QtQuick.Controls 2.15

Label {
    id: root
    property string score
    text: score
    color: "black"
    font {
        pointSize: 18
        bold: true
    }
}
