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
    color: "#303030"
    Material.accent: Material.Blue
    title: qsTr("Godzilla")

    Grid {
        id: grid
        x: 112
        y: 116
        width: 370
        height: 249
        flow: Grid.LeftToRight
        spacing: 20
        rows: 3
        columns: 2

        Text {
            id: element
            width: 116
            height: 47
            color: "#fbfbfb"
            text: qsTr("PORT: ")
            verticalAlignment: Text.AlignVCenter
            bottomPadding: -4
            horizontalAlignment: Text.AlignRight
            font.pixelSize: 18
        }

        TextField {
            id: textField1
            width: 176
            height: 47
            text: qsTr("")
        }




        Text {
            id: element3
            width: 116
            height: 47
            color: "#fbfbfb"
            text: qsTr("IP: ")
            leftPadding: -2
            font.family: "Verdana"
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
            horizontalAlignment: Text.AlignRight
        }

        TextField {
            id: textField
            width: 176
            height: 47
            text: qsTr("")
        }

    }

    Button {
        id: button
        x: 263
        y: 253
        text: qsTr("Connect")
        focusPolicy: Qt.WheelFocus
        anchors.horizontalCenter: grid.horizontalCenter
    }

}
/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_height:47;anchors_width:176}
}
 ##^##*/
