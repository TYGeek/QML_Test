import QtQuick 2.14
import QtQuick.Window 2.14
import visual 1.0

Window {

    width: 640
    height: 200

    visible: true
    title: qsTr("Hello World")

    Controller {
       id:connector
       onSignalValueChanged:
       {
           txt.text = value
       }
    }

    Text {
        id: txt
        objectName: "textObj"
        height: 100
        width: 100
        text: connector.result
        anchors.top: parent.top
        anchors.left: parent.left

    }

    Button {
        id: idStart
        objectName: "btnStart"
        text: "Start"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        onClicked: connector.start()
    }

    Button {
        id: idStop
        objectName: "btnStop"
        anchors.left: idStart.right
        anchors.bottom: parent.bottom
        text: "Stop"
        onClicked: connector.stop()
    }

    Button {
        id: idPause
        objectName: "btnPause"
        anchors.left: idStop.right
        anchors.bottom: parent.bottom
        text: "Pause/Resume"
        onClicked: connector.pause()
    }


}
