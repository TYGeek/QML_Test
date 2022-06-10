import QtQuick 2.0

Image {
    property alias text: txt.text
    signal clicked();
    source: "icons/Blue_Button.png"

   width: 110*2
   height: 34*2

    Text {
        id: txt
        color: "red"
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked();
    }
}
