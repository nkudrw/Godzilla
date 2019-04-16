import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.folderlistmodel 2.12

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    Material.accent: Material.Blue
    Material.theme: Material.Light
    Material.foreground: Material.Grey
    Material.primary: Material.Blue

    title: qsTr("Debug")

    Grid {
        id: grid
        x: 112
        y: 116
        width: 370
        height: 249
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 28
        flow: Grid.LeftToRight
        rows: 3
        columns: 2

        Grid {
            id: gridinside
            rows: 2
            columns: 2
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Text {
                id: element3
                width: 75
                height: 47
                text: qsTr("Main Camera")
                font.bold: false
                font.wordSpacing: -0.2
                style: Text.Normal
                verticalAlignment: Text.AlignVCenter
                font.family: "MS UI Gothic"
                font.pointSize: 10
            }

            TextField {
                id: port
                width: 176
                height: 47
                bottomPadding: 18
                topPadding: 13
                placeholderText: "Port"

            }

            Text {
                id: element2
                width: 75
                height: 47
                text: qsTr("Sub  Camera")
                font.family: "MS UI Gothic"
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                id: ipAddress
                width: 176
                height: 47
                text: qsTr("192.168.")
                bottomPadding: 18
                topPadding: 13
            }

        }

        Button {
            id: connect
            text: qsTr("Connect")
            anchors.verticalCenterOffset: 23
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            transformOrigin: Item.Center
            checkable: false
            highlighted: true
            focusPolicy: Qt.WheelFocus
            onClicked: {
                god.createUdpSocket(port.text);
                god.addSubCam(ipAddress.text);
            }
        }




    }

    Pane {
        id: pane1
        x: 111
        y: 74
        width: 418
        height: 307
        z: -1

        Material.elevation: 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }








}