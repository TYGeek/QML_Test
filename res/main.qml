import QtQuick 2.15
import QtQuick.Window 2.15
//import visual
Window {

    width: 640
    height: 200

    visible: true
    title: qsTr("Hello World")

//    CppConnection
//    {
//        : txt.text = result
//    }
    Text {
        id: txt
        objectName: "textObj"
        height: 100
        width: 100
        text: "12"
        anchors.top: parent.top
        anchors.left: parent.left
    }

    Button {
        id: idStart
        objectName: "btnStart"
        text: "Start"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }

    Button {
        id: idStop
        objectName: "btnStop"
        anchors.left: idStart.right
        anchors.bottom: parent.bottom
        text: "Stop"
    }

    Button {
        id: idPause
        objectName: "btnPause"
        anchors.left: idStop.right
        anchors.bottom: parent.bottom
        text: "Pause"
    }


}
