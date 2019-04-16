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

    title: qsTr("Godzilla")


    Pane {
        id: pane1
        x: 111
        y: 74
        width: 502
        height: 379
        hoverEnabled: true
        contentHeight: 1
        focusPolicy: Qt.ClickFocus
        anchors.verticalCenterOffset: 1
        anchors.horizontalCenterOffset: 0
        z: -1

        Material.elevation: 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    Flow {
        id: maincamport
        x: 271
        y: 93
        width: 263
        height: 58
        spacing: -33

        TextField {
            id: port
            width: 176
            height: 47
            text: "1111"
            bottomPadding: 18
            topPadding: 13
            placeholderText: ""

        }


    }

    Text {
        id: maincam
        x: 153
        y: 59
        width: 75
        height: 51
        text: qsTr("MainCamera")
        font.underline: true
        font.bold: false
        font.pointSize: 10
        verticalAlignment: Text.AlignVCenter
        font.family: "MS UI Gothic"
        clip: false
    }

    Flow {
        id: subcam
        x: 153
        y: 160
        width: 83
        height: 46

        Text {
            id: element2
            width: 75
            height: 51
            text: qsTr("SubCamera")
            font.strikeout: false
            font.underline: true
            clip: false
            font.family: "MS UI Gothic"
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter
        }
    }

    Flow {
        id: subcamip
        x: 271
        y: 194
        width: 400
        height: 43

        TextField {
            id: ipAddress
            width: 176
            height: 47
            text: qsTr("192.168.0.10")
            horizontalAlignment: Text.AlignLeft
            leftPadding: 2
            bottomPadding: 18
            topPadding: 13
        }

    }

    Flow {
        id: subcamposition
        x: 271
        y: 243
        width: 394
        height: 35
        spacing: 27

        TextField {
            id: subcam_x
            width: 68
            height: 40
            text: qsTr("0")
            horizontalAlignment: Text.AlignHCenter
            placeholderText: "X[mm]"
        }

        TextField {
            id: subcam_y
            width: 68
            height: 40
            text: qsTr("1000")
            horizontalAlignment: Text.AlignHCenter
            placeholderText: "Y[mm]"
        }

        TextField {
            id: subcam_z
            width: 68
            height: 40
            text: qsTr("0")
            horizontalAlignment: Text.AlignHCenter
            placeholderText: "Z[mm]"
        }


    }

    Flow {
        id: subcamangle
        x: 271
        y: 289
        width: 394
        height: 35

        TextField {
            id: subcam_angle
            width: 68
            height: 40
            text: qsTr("")
            horizontalAlignment: Text.AlignHCenter
            placeholderText: ""
        }
        spacing: 27
    }




    Text {
        id: maincam1
        x: 190
        y: 108
        width: 75
        height: 23
        color: "#989494"
        text: "PORT"
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
        clip: false
        font.family: "MS UI Gothic"
    }

    Text {
        id: maincam2
        x: 205
        y: 204
        width: 75
        height: 23
        color: "#989494"
        text: "IP"
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
        font.family: "MS UI Gothic"
        clip: false
    }

    Text {
        id: maincam3
        x: 175
        y: 249
        width: 75
        height: 23
        color: "#989494"
        text: "XYZ [mm]"
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
        clip: false
        font.family: "MS UI Gothic"
    }

    Text {
        id: maincam4
        x: 175
        y: 295
        width: 75
        height: 23
        color: "#989494"
        text: "Angle[°]"
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
        clip: false
        font.family: "MS UI Gothic"
    }

    Button {
        id: connect
        x: 281
        y: 354
        text: qsTr("Connect")
        spacing: 4
        autoRepeat: false
        autoExclusive: false
        checked: false
        wheelEnabled: false
        checkable: false
        highlighted: true
        focusPolicy: Qt.TabFocus
        onClicked: {
            god.createUdpSocket(port.text);
            god.addSubCam(ipAddress.text, subcam_x.text, subcam_y.text, subcam_z.text, subcam_angle);
        }
    }


}























