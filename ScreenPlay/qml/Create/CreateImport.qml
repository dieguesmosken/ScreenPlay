import QtQuick 2.9
import QtAV 1.07
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.2

Item {
    id: createImport
    anchors.fill: parent
    state: "out"
    Component.onCompleted: state = "in"
    property bool isVideoPlaying: true
    property url file
    onFileChanged: {
        timerSource.start()
    }

    Timer {
        id: timerSource
        interval: 1000
        onTriggered: {
            //var tmp = Qt.resolvedUrl(file).toString()
            player.source = Qt.resolvedUrl(file)
            player.play()
        }
    }

    RectangularGlow {
        id: effect
        anchors {
            top: videoOutWrapper.top
            left: videoOutWrapper.left
            right: videoOutWrapper.right
            topMargin: 3
        }

        height: videoOutWrapper.height
        width: videoOutWrapper.width
        cached: true
        z: 9
        glowRadius: 3
        spread: 0.2
        color: "black"
        opacity: 0.4
        cornerRadius: 15
    }

    Rectangle {
        id: videoOutWrapper
        width: 450
        height: 263
        z: 12
        color: "black"
        anchors {
            top: parent.top
            topMargin: 180
            horizontalCenter: parent.horizontalCenter
        }

        VideoOutput2 {
            id: videoOut
            z: 13
            anchors.fill: parent
            source: player
            opengl: true
            fillMode: VideoOutput.Stretch

            Slider {
                id: sliVideoPosition
                height: 30
                width: parent.width * .8
                from: 0
                to: 1
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    bottom: parent.bottom
                    bottomMargin: 20
                }
                onValueChanged: {
                    print(player.position)
                    player.seek(sliVideoPosition.value * player.duration)
                }
            }

            Image {
                id: imgPreview
                anchors.fill: parent
                opacity: 0
            }

            BusyIndicator {
                id: busyIndicator
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                visible: false
            }
            Text {
                id: txtDescriptionThumbnail
                text: qsTr("Select preview image")
                font.family: "Roboto"
                opacity: .5
                renderType: Text.NativeRendering
                font.pixelSize: 14
                color: "white"
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    bottom: parent.bottom
                    bottomMargin: 10
                }
            }
        }
    }

    MediaPlayer {
        id: player
        videoCodecPriority: ["CUDA", "D3D11", "DXVA", "VAAPI", "FFmpeg"]
        autoPlay: true
        loops: MediaPlayer.Infinite
        volume: 0
        onSeekFinished: {
            busyIndicator.visible = false
            pause()
            print(player.metaData.videoFrameRate)
        }
    }

    RectangularGlow {
        id: effect2
        anchors {
            top: contentWrapper.top
            left: contentWrapper.left
            right: contentWrapper.right
            topMargin: 3
        }

        height: contentWrapper.height
        width: contentWrapper.width
        cached: true
        z: 9
        glowRadius: 3
        spread: 0.2
        color: "black"
        opacity: 0.4
        cornerRadius: 15
    }

    Rectangle {
        id: contentWrapper
        width: 800
        height: 300
        z: 10
        radius: 4
        anchors {
            top: parent.top
            topMargin: 300
            horizontalCenter: parent.horizontalCenter
        }

        Item {
            id: chooseImageWrapper
            height: 60
            anchors {
                top: parent.top
                topMargin: 50
                right: parent.right
                left: parent.left
            }

            FileDialog {
                id: fileDialogOpenPreview
                nameFilters: ["Image files (*.jpg *.png)"]
                onAccepted: {
                    imgPreview.source = currentFile
                    imgPreview.opacity = 1
                    //currentFile
                }
            }

            Button {
                id: btnChooseImage
                text: qsTr("Select Image Manually")
                Material.background: Material.Orange
                Material.foreground: "white"
                icon.source: "qrc:/assets/icons/icon_folder_open.svg"
                icon.color: "white"
                icon.width: 16
                icon.height: 16
                anchors.centerIn: parent
                onClicked: fileDialogOpenPreview.open()
            }
        }

        Column {
            spacing: 20
            anchors {
                top: chooseImageWrapper.top
                topMargin: 50
                right: parent.right
                rightMargin: 78
                bottom: parent.bottom
                bottomMargin: 50
                left: parent.left
                leftMargin: 78
            }

            TextField {
                id: txtTitle
                height: 60
                width: parent.width
                selectByMouse: true
                text: qsTr("")
                placeholderText: "Title"
            }
        }

        Button {
            text: qsTr("Import Video")
            Material.background: Material.Orange
            Material.foreground: "white"
            icon.source: "qrc:/assets/icons/icon_upload.svg"
            icon.color: "white"
            icon.width: 16
            icon.height: 16
            anchors {
                bottom: parent.bottom
                bottomMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            onClicked: {

                if (txtTitle.text === ""
                        || txtTitle.placeholderText === "Text") {
                    txtTitle.select(0, 0)
                    txtTitle.focus = true
                    return
                }

                //Check if there are any other characters than space
                if (!(/\S/.test(txtTitle.text))) {
                    txtTitle.select(0, 0)
                    txtTitle.focus = true
                    return
                }

                if (fileDialogOpenPreview.currentFile != "") {
                    screenPlayCreate.importVideo(
                                txtTitle.text.replace(/\s/g, ''), file,
                                fileDialogOpenPreview.currentFile,
                                player.duration)
                } else {
                    screenPlayCreate.importVideo(
                                txtTitle.text.replace(/\s/g, ''), file,
                                player.position,
                                player.duration,
                                player.metaData.videoFrameRate)
                }
                player.stop()
                createImport.state = "out"
            }
        }
    }

    states: [
        State {
            name: "out"
            PropertyChanges {
                target: createImport
                opacity: 0
            }
            PropertyChanges {
                target: videoOutWrapper
                z: 0
                opacity: 0
                anchors.topMargin: 50
            }
            PropertyChanges {
                target: effect
                opacity: 0
                color: "transparent"
            }
            PropertyChanges {
                target: contentWrapper
                anchors.topMargin: -500
                opacity: 0
            }
        },
        State {
            name: "in"
            PropertyChanges {
                target: createImport
                opacity: 1
            }
            PropertyChanges {
                target: videoOut
                opacity: 1
            }
            PropertyChanges {
                target: effect
                opacity: .4
                color: "black"
            }
            PropertyChanges {
                target: contentWrapper
                opacity: 1
                anchors.topMargin: 300
            }
            PropertyChanges {
                target: videoOutWrapper
                z: 12
                opacity: 1
                anchors.topMargin: 70
            }
        }
    ]

    transitions: [
        Transition {
            from: "out"
            to: "in"
            reversible: true

            SequentialAnimation {
                PauseAnimation {
                    duration: 500
                }
                ParallelAnimation {
                    PropertyAnimation {
                        duration: 300
                        target: contentWrapper
                        property: "opacity"
                    }
                    PropertyAnimation {
                        duration: 300
                        target: contentWrapper
                        property: "anchors.topMargin"
                        easing.type: Easing.InOutQuad
                    }
                }
                ParallelAnimation {
                    PropertyAnimation {
                        duration: 250
                        target: videoOutWrapper
                        property: "opacity"
                    }
                    PropertyAnimation {
                        duration: 250
                        target: effect
                        properties: "color, opacity"
                    }
                }
            }
        }
    ]
}
