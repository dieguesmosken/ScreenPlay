import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.platform 1.1
import ScreenPlay 1.0


/*!
   \qmltype Image Selector
   \brief A image selector with popup preview.

   Test

   \image rootPreview.png

   \section1 Setting default text and capitalization

   Test

   \qml
        root {

        }
   \endqml

*/
Item {
    id: root
    height: 70
    width: parent.width
    state: "nothingSelected"

    property string imageSource
    property alias placeHolderText: txtPlaceholder.text

    onImageSourceChanged: {
        if (imageSource === "") {
            img.source = ""
            txtName.text = ""
            root.state = "nothingSelected"
        } else {
            img.source = imageSource
            root.state = "imageSelected"
        }
    }

    Rectangle {
        id: rectangle
        color: Material.theme === Material.Light ? Material.background : Qt.darker(
                                                       Material.background)
        radius: 3
        clip: true
        anchors {
            fill: parent
            margins: 3
        }

        Rectangle {
            id: imgWrapper
            width: 70
            radius: 3
            clip: true
            color: Material.color(Material.Grey, Material.Shade700)
            anchors {
                top: parent.top
                left: parent.left
                bottom: parent.bottom
                margins: 10
            }

            Image {
                id: img
                anchors.fill: parent
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    if (imageSource !== "") {
                        popup.open()
                    }
                }
            }
        }

        Popup {
            id: popup
            width: 902
            modal: true
            anchors.centerIn: Overlay.overlay
            height: 507
            Image {
                source: imageSource
                anchors.fill: parent
            }
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: popup.close()
            }
        }

        Text {
            id: txtPlaceholder
            clip: true
            font.pointSize: 12
            font.capitalization: Font.Capitalize
            text: qsTr("Set your own preview image")
            font.family: ScreenPlay.settings.font
            wrapMode: Text.WordWrap
            color: Material.secondaryTextColor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors {
                top: parent.top
                left: imgWrapper.right
                right: btnClear.left
                bottom: parent.bottom
                margins: 10
            }
        }

        Text {
            id: txtName
            clip: true
            font.pointSize: 12
            font.family: ScreenPlay.settings.font
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            color: Material.secondaryTextColor
            anchors {
                top: parent.top
                left: imgWrapper.right
                right: btnClear.left
                bottom: parent.bottom
                margins: 10
            }
        }

        Button {
            id: btnClear
            text: qsTr("Clear")
            Material.background: Material.theme
                                 === Material.Light ? Qt.lighter(
                                                          Material.accent) : Qt.darker(
                                                          Material.accent)
            Material.foreground: "white"

            anchors {
                top: parent.top
                right: btnOpen.left
                bottom: parent.bottom
                margins: 5
            }
            onClicked: imageSource = ""
        }

        Button {
            id: btnOpen
            text: qsTr("Select Preview Image")
            Material.background: Material.accent
            Material.foreground: "white"
            font.family: ScreenPlay.settings.font
            anchors {
                top: parent.top
                right: parent.right
                rightMargin: 10
                bottom: parent.bottom
                margins: 5
            }
            onClicked: fileDialog.open()
        }
        FileDialog {
            id: fileDialog
            title: "Please choose a file"
            fileMode: FileDialog.OpenFile
            nameFilters: ["Images (*.png *.jpg)"]
            onAccepted: {
                imageSource = fileDialog.file
                txtName.text = fileDialog.file.toString().replace(/^.*[\\\/]/,
                                                                  '')
            }
        }
    }

    states: [
        State {
            name: "imageSelected"
            PropertyChanges {
                target: btnClear
                opacity: 1
                anchors.topMargin: 5
            }
            PropertyChanges {
                target: txtPlaceholder
                opacity: 0
            }
        },
        State {
            name: "nothingSelected"
            PropertyChanges {
                target: btnClear
                opacity: 0
                anchors.topMargin: -40
            }
        }
    ]

    transitions: [
        Transition {
            from: "imageSelected"
            to: "nothingSelected"
            reversible: true
            PropertyAnimation {
                target: btnClear
                properties: "opacity, anchors.topMargin"
                duration: 300
                easing.type: Easing.OutQuart
            }
            PropertyAnimation {
                target: txtPlaceholder
                property: "opacity"
                duration: 300
                easing.type: Easing.OutQuart
            }
        }
    ]
}
