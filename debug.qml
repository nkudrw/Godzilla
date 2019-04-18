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
        id: targetdis
        x: 240
        y: 85
        width: 82
        height: 58
        spacing: -33

        TextField {
            id: distance
            width: 80
            height: 47
            text: god._lensinfo.focus
            horizontalAlignment: Text.AlignHCenter
            bottomPadding: 18
            topPadding: 13
            placeholderText: ""

        }


    }

    Text {
        id: targetinfo
        x: 101
        y: 45
        width: 75
        height: 51
        text: qsTr("Target Info")
        font.underline: true
        font.bold: false
        font.pointSize: 10
        verticalAlignment: Text.AlignVCenter
        font.family: "MS UI Gothic"
        clip: false
    }

    Flow {
        id: subcam
        x: 101
        y: 212
        width: 83
        height: 46

        Text {
            id: element2
            width: 75
            height: 51
            text: qsTr("SubCam Info")
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
        x: 240
        y: 246
        width: 95
        height: 43

        TextField {
            id: pan
            width: 80
            height: 47
           // text: god.getSubCamLensInfo(0).pan
            horizontalAlignment: Text.AlignHCenter
            leftPadding: 2
            bottomPadding: 18
            topPadding: 13
        }

    }

    Flow {
        id: subcamposition
        x: 240
        y: 182
        width: 394
        height: 35
        spacing: 27

        TextField {
            id: target_x
            width: 80
            height: 40
            text: god._targetPosi.x
            horizontalAlignment: Text.AlignHCenter
            placeholderText: ""
        }

        TextField {
            id: target_y
            width: 80
            height: 40
            text: god._targetPosi.y
            horizontalAlignment: Text.AlignHCenter
            placeholderText: ""
        }

        TextField {
            id: target_z
            width: 80
            height: 40
            text: god._targetPosi.z
            horizontalAlignment: Text.AlignHCenter
            placeholderText: ""
        }


    }

    Flow {
        id: subcamangle
        x: 240
        y: 323
        width: 394
        height: 35

        TextField {
            id: angle
            width: 80
            height: 40
           // text: god.getSubCamLensInfo(0).zoom
            horizontalAlignment: Text.AlignHCenter
            placeholderText: ""
        }
        spacing: 27
    }




    Text {
        id: maincam1
        x: 101
        y: 102
        width: 75
        height: 23
        color: "#989494"
        text: "Distance[mm]"
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
        clip: false
        font.family: "MS UI Gothic"
    }

    Text {
        id: maincam2
        x: 142
        y: 266
        width: 75
        height: 23
        color: "#989494"
        text: "Pan[°]"
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
        font.family: "MS UI Gothic"
        clip: false
    }

    Text {
        id: maincam3
        x: 131
        y: 188
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
        x: 131
        y: 335
        width: 75
        height: 23
        color: "#989494"
        text: "Angle[°]"
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
        clip: false
        font.family: "MS UI Gothic"
    }

    Text {
        id: maincam5
        x: 131
        y: 150
        width: 75
        height: 23
        color: "#989494"
        text: "Size [mm]"
        font.family: "MS UI Gothic"
        clip: false
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
    }

    Flow {
        id: maincamport1
        x: 240
        y: 132
        width: 82
        height: 58
        spacing: -33
        TextField {
            id: size
            width: 80
            height: 47
            text: ""
            horizontalAlignment: Text.AlignHCenter
            topPadding: 13
            placeholderText: ""
            bottomPadding: 18
        }
    }

    Text {
        id: maincam6
        x: 147
        y: 300
        width: 75
        height: 23
        color: "#989494"
        text: "Tilt[°]"
        font.family: "MS UI Gothic"
        clip: false
        font.pointSize: 13
        verticalAlignment: Text.AlignVCenter
    }

    Flow {
        id: subcamip1
        x: 240
        y: 280
        width: 95
        height: 43
        TextField {
            id: tilt
            width: 80
            height: 47
           // text: god.getSubCamLensInfo(0).tilt
            horizontalAlignment: Text.AlignHCenter
            topPadding: 13
            leftPadding: 2
            bottomPadding: 18
        }
    }


}























