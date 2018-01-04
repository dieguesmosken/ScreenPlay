import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.0

Item {
    id: settingsWrapper
    anchors.fill: parent

    Connections {
        target: screenPlaySettings
        onDecoderChanged: {
            if (decoder === "CUDA") {
                settingsComboBox.currentIndex = 0
            } else if (decoder === "D3D11") {
                settingsComboBox.currentIndex = 1
            } else if (decoder === "DXVA") {
                settingsComboBox.currentIndex = 2
            } else if (decoder === "VAAPI") {
                settingsComboBox.currentIndex = 3
            } else if (decoder === "FFmpeg") {
                settingsComboBox.currentIndex = 4
            }
        }
    }

    Flickable {
        id: flickableWrapper
        width: 800
        height: parent.height
        contentHeight: columnWrapper.childrenRect.height
        contentWidth: 800
        flickableDirection: Flickable.VerticalFlick
        maximumFlickVelocity: 7000
        flickDeceleration: 5000

        anchors {
            top: parent.top
            topMargin: 20
            bottom:parent.bottom
            bottomMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        ScrollBar.vertical: ScrollBar {
            snapMode: ScrollBar.SnapOnRelease
        }
        Column {
            id: columnWrapper
            anchors.margins: 20
            //            height: 1200
            width: 760
            spacing: 30

            Item {
                id: settingsGeneralWrapper
                height: 390
                width: parent.width

                RectangularGlow {
                    id: effectBtnEmpty
                    anchors {
                        top: parent.top
                    }

                    height: parent.height
                    width: parent.width
                    cached: true
                    glowRadius: 3
                    spread: 0.2
                    color: "black"
                    opacity: 0.2
                    cornerRadius: 15
                }

                Rectangle {
                    anchors.fill: parent
                    radius: 4
                    clip: true

                    SettingsHeader {
                        id: headerGeneral
                        text: qsTr("General")
                        anchors {
                            top: parent.top
                            left: parent.left
                            right: parent.right
                        }
                    }

                    Column {
                        spacing: 10
                        anchors {
                            top: headerGeneral.bottom
                            margins: 20
                            right: parent.right
                            bottom: parent.bottom
                            left: parent.left
                        }
                        SettingBool {
                            headline: qsTr("Autostart")
                            description: qsTr("ScreenPlay will start with Windows and will setup your Desktop every time for you.")
                            isChecked: screenPlaySettings.autostart
                            onCheckboxChanged: {
                                screenPlaySettings.setAutostart(checked)
                                screenPlaySettings.writeSingleSettingConfig(
                                            "autostart", checked)
                            }
                        }
                        SettingsHorizontalSeperator {
                        }
                        SettingBool {
                            headline: qsTr("High priority Autostart")
                            available: false

                            description: qsTr("This options grants ScreenPlay a higher autostart priority than other apps.")
                            isChecked: screenPlaySettings.highPriorityStart
                            onCheckboxChanged: {
                                screenPlaySettings.setHighPriorityStart(checked)
                                screenPlaySettings.writeSingleSettingConfig(
                                            "highPriorityStart", checked)
                            }
                        }
                        SettingsHorizontalSeperator {
                        }
                        SettingsButton {
                            headline: qsTr("Set save location")
                            description: screenPlaySettings.localStoragePath //qsTr("Choose where to find you content. The default save location is you steam installation")
                            buttonText: qsTr("Set save location")
                            onButtonPressed: {
                                folderDialogSaveLocation.open()
                            }
                            FolderDialog {
                                id: folderDialogSaveLocation
                                onAccepted: {
                                    screenPlaySettings.setLocalStoragePath(
                                                folderDialogSaveLocation.currentFolder)
                                }
                            }
                        }
                        SettingsHorizontalSeperator {
                        }
                        SettingBool {
                            headline: qsTr("Send anonymous crash reports and statistics")
                            description: qsTr("Help us make ScreenPlay faster and more stable. All collected data is purely used for development purposes!")
                            isChecked: screenPlaySettings.sendStatistics
                            onCheckboxChanged: {
                                screenPlaySettings.setSendStatistics(checked)
                                screenPlaySettings.writeSingleSettingConfig("sendStatistics",checked)
                            }
                        }
                    }
                }
            }

            Item {
                id: settingsPerformanceWrapper
                height: 150
                width: parent.width

                RectangularGlow {
                    id: effect2
                    anchors {
                        top: parent.top
                    }

                    height: parent.height
                    width: parent.width
                    cached: true
                    glowRadius: 3
                    spread: 0.2
                    color: "black"
                    opacity: 0.2
                    cornerRadius: 15
                }

                Rectangle {
                    anchors.fill: parent
                    radius: 4
                    clip: true

                    SettingsHeader {
                        id: headerPerformance
                        text: qsTr("Performance")
                        image: "qrc:/assets/icons/icon_build.svg"
                        anchors {
                            top: parent.top
                            left: parent.left
                            right: parent.right
                        }
                    }

                    Column {
                        anchors {
                            top: headerPerformance.bottom
                            margins: 20
                            right: parent.right
                            bottom: parent.bottom
                            left: parent.left
                        }
                        spacing: 10

                        SettingsComboBox {
                            id: settingsComboBox
                            headline: qsTr("Set decoder")
                            description: qsTr("ScreenPlay supports different encoders for different hardware requirements.")
                            onCurrentIndexChanged: {
                                screenPlaySettings.setDecoder(
                                            settingsComboBox.comboBoxListModel.get(
                                                settingsComboBox.currentIndex).text.toString(
                                                ))
                            }
                            comboBoxListModel: ListModel {
                                id: model
                                ListElement {
                                    text: "CUDA"
                                }
                                ListElement {
                                    text: "D3D11"
                                }
                                ListElement {
                                    text: "DXVA"
                                }
                                ListElement {
                                    text: "VAAPI"
                                }
                                ListElement {
                                    text: "FFmpeg"
                                }
                            }
                        }
                    }
                }
            }

            Item {
                id: settingsAboutrapper
                height: 350
                width: parent.width

                RectangularGlow {
                    id: effect3
                    anchors {
                        top: parent.top
                    }

                    height: parent.height
                    width: parent.width
                    cached: true
                    glowRadius: 3
                    spread: 0.2
                    color: "black"
                    opacity: 0.2
                    cornerRadius: 15
                }

                Rectangle {
                    anchors.fill: parent
                    radius: 4
                    clip: true

                    SettingsHeader {
                        id: headerAbout
                        text: qsTr("About")
                        image: "qrc:/assets/icons/icon_cake.svg"
                        anchors {
                            top: parent.top
                            left: parent.left
                            right: parent.right
                        }
                    }

                    Column {
                        width: parent.width
                        spacing: 10
                        anchors {
                            top: headerAbout.bottom
                            left: parent.left
                            right: parent.right
                            margins: 20
                        }

                        Item {
                            width: parent.width
                            height: 180
                            Text {
                                id: txtHeadline
                                color: "#5D5D5D"
                                text: "Lore Ipsum"
                                renderType: Text.NativeRendering
                                verticalAlignment: Text.AlignVCenter
                                horizontalAlignment: Text.AlignLeft
                                font.pixelSize: 16
                                anchors {
                                    top: parent.top
                                    topMargin: 6
                                    left: parent.left
                                    leftMargin: 20
                                }
                            }
                            Text {
                                id: txtDescription
                                text: "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis, sem. \n \n Nulla consequat massa quis enim. Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. "
                                color: "#B5B5B5"
                                renderType: Text.NativeRendering
                                wrapMode: Text.WordWrap
                                verticalAlignment: Text.AlignTop
                                horizontalAlignment: Text.AlignLeft
                                font.pixelSize: 14
                                font.family: "Roboto"
                                width: parent.width *.6
                                anchors{
                                    top:txtHeadline.bottom
                                    topMargin: 6
                                    left:parent.left
                                    leftMargin: 20
                                    right:imgLogoHead.left
                                    rightMargin: 20
                                    bottom: parent.bottom
                                }
                            }
                            Image {
                                id: imgLogoHead
                                source: "qrc:/assets/icons/icon_logo_head.svg"
                                width: 150
                                height: 150
                                sourceSize: Qt.size(150,150)
                                anchors{
                                    top:txtHeadline.bottom
                                    topMargin: -10
                                    right:parent.right
                                    rightMargin: 20

                                }
                            }
                        }
                        SettingsHorizontalSeperator {
                        }
                        SettingsButton {
                            headline: qsTr("Third Party Software")
                            description: qsTr("ScreenPlay would not be possible without the work of others. A big thank you to: ")
                            buttonText: qsTr("Licenses")
                            onButtonPressed: {

                            }
                        }

                    }
                }
            }
        }
    }
}