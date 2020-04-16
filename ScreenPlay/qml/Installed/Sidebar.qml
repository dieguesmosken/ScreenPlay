import QtQuick 2.12
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.12
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.12

import ScreenPlay 1.0
import Settings 1.0

import "../Monitors"
import "../Common" as SP

Item {
    id: root
    width: 400
    state: "inactive"
    focus: true

    property real navHeight
    property string type
    property string activeScreen

    function indexOfValue(model, value) {

        for (var i = 0; i < model.length; i++) {
            let ourValue = model[i].value
            if (value === ourValue)
                return i
        }
        return -1
    }

    Connections {
        target: ScreenPlay.util

        function onSetSidebarItem(screenId, type) {

            // Toggle sidebar if clicked on the same content twice
            if (activeScreen === screenId && root.state !== "inactive") {
                root.state = "inactive"
                return
            }

            activeScreen = screenId
            root.type = type

            switch (type) {
            case "videoWallpaper":
                state = "videoWallpaper"
                return
            case "htmlWallpaper":
                state = "activeScene"
                return
            case "qmlWallpaper":
                state = "activeScene"
                return
            case "godotWallpaper":
                state = "activeScene"
                return
            case "qmlWidget":
                state = "activeWidget"
                return
            case "htmlWidget":
                state = "activeWidget"
                return
            case "standaloneWidget":
                state = "activeWidget"
                return
            }
        }
    }

    MouseArea {
        id: mouseAreaHelper
        anchors.fill: parent
        enabled: true
    }

    onActiveScreenChanged: {
        txtHeadline.text = ScreenPlay.installedListModel.get(
                    activeScreen).screenTitle

        if (ScreenPlay.installedListModel.get(
                    activeScreen).screenPreviewGIF === undefined) {
            image.source = Qt.resolvedUrl(
                        ScreenPlay.globalVariables.localStoragePath + "/"
                        + activeScreen + "/" + ScreenPlay.installedListModel.get(
                            activeScreen).screenPreview)
            image.playing = false
        } else {

            image.source = Qt.resolvedUrl(
                        ScreenPlay.globalVariables.localStoragePath + "/"
                        + activeScreen + "/" + ScreenPlay.installedListModel.get(
                            activeScreen).screenPreviewGIF)
            image.playing = true
        }
    }

    Item {
        id: sidebarWrapper
        anchors.fill: parent

        Item {
            id: navBackground
            height: navHeight
            anchors {
                top: parent.top
                right: parent.right
                left: parent.left
            }

            LinearGradient {
                anchors.fill: parent
                start: Qt.point(0, 0)
                end: Qt.point(400, 0)
                gradient: Gradient {
                    GradientStop {
                        position: 0.0
                        color: "transparent"
                    }
                    GradientStop {
                        position: 0.1
                        color: "#AAffffff"
                    }
                    GradientStop {
                        position: 1.0
                        color: "#ffffff"
                    }
                }
            }
        }

        Rectangle {
            id: sidebarBackground
            color: "white"
            anchors {
                top: navBackground.bottom
                right: parent.right
                bottom: parent.bottom
                left: parent.left
                leftMargin: 5
            }

            Rectangle {
                id: imageWrapper
                height: 237
                color: "#2b2b2b"
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0

                AnimatedImage {
                    id: image
                    playing: true
                    fillMode: Image.PreserveAspectCrop
                    asynchronous: true
                    anchors.fill: parent
                    onStatusChanged: {
                        if (image.status === Image.Error) {
                            source = "qrc:/assets/images/missingPreview.png"
                        }
                    }
                }
                LinearGradient {
                    id: tabShadow
                    height: 50
                    cached: true

                    anchors {
                        bottom: parent.bottom
                        right: parent.right
                        left: parent.left
                    }
                    start: Qt.point(0, 50)
                    end: Qt.point(0, 0)
                    gradient: Gradient {
                        GradientStop {
                            position: 0.0
                            color: "#EE000000"
                        }
                        GradientStop {
                            position: 1.0
                            color: "#00000000"
                        }
                    }
                }

                Text {
                    id: txtHeadline
                    text: qsTr("Headline")
                    font.family: ScreenPlay.settings.font
                    font.weight: Font.Thin
                    verticalAlignment: Text.AlignBottom
                    font.pointSize: 16
                    color: "white"
                    wrapMode: Text.WordWrap
                    height: 50
                    anchors {
                        bottom: parent.bottom
                        right: parent.right
                        margins: 20
                        left: parent.left
                    }
                }

                MouseArea {
                    id: button
                    height: 50
                    width: 50
                    anchors.top: parent.top
                    anchors.left: parent.left
                    cursorShape: Qt.PointingHandCursor
                    onClicked: root.state = "inactive"

                    Image {
                        id: imgBack
                        source: "qrc:/assets/icons/icon_arrow_right.svg"
                        sourceSize: Qt.size(15, 15)
                        fillMode: Image.PreserveAspectFit
                        anchors.centerIn: parent
                    }
                }
            }

            ColumnLayout {
                spacing: 20

                anchors {
                    top: imageWrapper.bottom
                    right: parent.right
                    left: parent.left
                    margins: 30
                }

                ColumnLayout {
                    Layout.fillWidth: true

                    Text {
                        id: txtHeadlineMonitor
                        height: 20
                        text: qsTr("Select a Monitor to display the content")
                        font.family: ScreenPlay.settings.font
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                        color: "#626262"
                    }

                    MonitorSelection {
                        id: monitorSelection
                        height: 180
                        Layout.fillWidth: true
                        availableWidth: width
                        availableHeight: height
                        fontSize: 11
                    }
                }

                SP.Slider {
                    id: sliderVolume
                    stepSize: 0.01
                    from: 0
                    value: 1
                    to: 1
                    Layout.fillWidth: true
                    headline: qsTr("Set Volume")
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 5

                    Text {
                        visible: false
                        id: txtComboBoxFillMode
                        text: qsTr("Fill Mode")

                        font.family: ScreenPlay.settings.font
                        verticalAlignment: Text.AlignVCenter
                        font.pointSize: 10
                        color: "#626262"
                        wrapMode: Text.WrapAnywhere
                        Layout.fillWidth: true
                    }
                    ComboBox {
                        id:cbVideoFillMode
                        visible: false
                        Layout.fillWidth: true
                        textRole: "text"
                        valueRole: "value"
                        font.family: ScreenPlay.settings.font
                        currentIndex:   root.indexOfValue(
                                        cbVideoFillMode.model,
                                        ScreenPlay.settings.videoFillMode)


                        model: [{
                                "value": Settings.Stretch,
                                "text": qsTr("Stretch")
                            }, {
                                "value": Settings.Fill,
                                "text": qsTr("Fill")
                            }, {
                                "value": Settings.Contain,
                                "text": qsTr("Contain")
                            }, {
                                "value": Settings.Cover,
                                "text": qsTr("Cover")
                            }, {
                                "value": Settings.Scale_Down,
                                "text": qsTr("Scale-Down")
                            }]
                    }
                }
            }

            Button {
                id: btnSetWallpaper
                text: qsTr("Set wallpaper")
                Material.accent: Material.Orange
                Material.background: Material.Orange
                Material.foreground: "white"
                font.family: ScreenPlay.settings.font
                icon.source: "qrc:/assets/icons/icon_plus.svg"
                icon.color: "white"
                icon.width: 16
                icon.height: 16
                enabled: {
                    if (type.endsWith("Wallpaper")) {
                        if (monitorSelection.activeMonitors.length > 0) {
                            return true
                        }
                    } else if (type.endsWith("Widget")) {
                        return true
                    }
                    return false
                }

                anchors {
                    bottom: parent.bottom
                    bottomMargin: 20
                    horizontalCenter: parent.horizontalCenter
                }

                onClicked: {
                    if (type.endsWith("Wallpaper")) {
                        let activeMonitors = monitorSelection.getActiveMonitors(
                                )

                        // TODO Alert user to choose a monitor
                        if (activeMonitors.length === 0)
                            return

                        ScreenPlay.screenPlayManager.createWallpaper(
                                    activeMonitors, ScreenPlay.globalVariables.localStoragePath
                                    + "/" + activeScreen,
                                    ScreenPlay.installedListModel.get(activeScreen).screenPreview,
                                    (Math.round(sliderVolume.value * 100) / 100),
                                    cbVideoFillMode.currentText, type)
                    } else {
                        ScreenPlay.screenPlayManager.createWidget(
                                    ScreenPlay.globalVariables.localStoragePath
                                    + "/" + activeScreen,
                                    ScreenPlay.installedListModel.get(
                                        activeScreen).screenPreview, type)
                    }
                    root.state = "inactive"
                    monitorSelection.deselectAll()
                }
            }
        }

        Item {
            id: shadow
            width: 5

            anchors {
                top: parent.top
                right: sidebarBackground.left
                bottom: parent.bottom
                left: parent.left
            }

            LinearGradient {
                anchors.fill: parent
                start: Qt.point(0, 0)
                end: Qt.point(5, 0)
                gradient: Gradient {
                    GradientStop {
                        position: 0.0
                        color: "#00000000"
                    }
                    GradientStop {
                        position: 1.0
                        color: "#22000000"
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "active"

            PropertyChanges {
                target: mouseAreaHelper
                enabled: true
            }

            PropertyChanges {
                target: root
                anchors.rightMargin: 0
            }
            PropertyChanges {
                target: image
                opacity: 1
                anchors.topMargin: 0
            }
            PropertyChanges {
                target: btnSetWallpaper
                text: qsTr("Set Wallpaper")
            }
            PropertyChanges {
                target: txtHeadlineMonitor
                opacity: 1
            }
        },
        State {
            name: "inactive"

            PropertyChanges {
                target: mouseAreaHelper
                enabled: false
            }

            PropertyChanges {
                target: root
                anchors.rightMargin: -root.width
            }
            PropertyChanges {
                target: image
                opacity: 0
                anchors.topMargin: 20
            }
        },
        State {
            name: "activeWidget"
            PropertyChanges {
                target: mouseAreaHelper
                enabled: true
            }

            PropertyChanges {
                target: sliderVolume
                visible: false
            }

            PropertyChanges {
                target: monitorSelection
                visible: false
                enabled: false
            }

            PropertyChanges {
                target: image
                opacity: 1
                anchors.topMargin: 0
            }

            PropertyChanges {
                target: btnSetWallpaper
                text: qsTr("Create Widget")
            }
            PropertyChanges {
                target: txtHeadlineMonitor
                opacity: 0
            }
        },
        State {
            name: "activeScene"
            PropertyChanges {
                target: mouseAreaHelper
                enabled: true
            }

            PropertyChanges {
                target: image
                opacity: 1
                anchors.topMargin: 0
            }
            PropertyChanges {
                target: btnSetWallpaper
                text: qsTr("Create Wallpaper")
            }
            PropertyChanges {
                target: txtHeadlineMonitor
                opacity: 1
            }
            PropertyChanges {
                target: sliderVolume
                opacity: 0
                visible: false
            }
        },
        State {
            name: "videoWallpaper"
            PropertyChanges {
                target: mouseAreaHelper
                enabled: true
            }

            PropertyChanges {
                target: image
                opacity: 1
                anchors.topMargin: 0
            }

            PropertyChanges {
                target: btnSetWallpaper
                text: qsTr("Create Wallpaper")
            }
            PropertyChanges {
                target: txtHeadlineMonitor
                opacity: 1
            }

            PropertyChanges {
                target: txtComboBoxFillMode
                opacity: 1
                visible: true
            }

            PropertyChanges {
                target: cbVideoFillMode
                opacity: 1
                visible: true
            }
        }
    ]

    transitions: [
        Transition {
            to: "active"

            SequentialAnimation {
                NumberAnimation {
                    target: root
                    properties: "anchors.rightMargin"
                    duration: 250
                    easing.type: Easing.OutQuart
                }

                ParallelAnimation {
                    NumberAnimation {
                        target: image
                        property: "opacity"
                        duration: 200
                    }
                    NumberAnimation {
                        target: image
                        property: "anchors.topMargin"
                        duration: 100
                    }
                }
            }
        },
        Transition {
            to: "inactive"

            NumberAnimation {
                target: image
                property: "opacity"
                duration: 200
            }
            NumberAnimation {
                target: image
                property: "anchors.topMargin"
                duration: 400
            }

            NumberAnimation {
                target: root
                properties: "anchors.rightMargin"
                duration: 250
                easing.type: Easing.OutQuart
            }
        },
        Transition {
            to: "activeWidget"

            SequentialAnimation {
                NumberAnimation {
                    target: root
                    properties: "anchors.rightMargin"
                    duration: 250
                    easing.type: Easing.OutQuart
                }

                ParallelAnimation {
                    NumberAnimation {
                        target: image
                        property: "opacity"
                        duration: 200
                    }
                    NumberAnimation {
                        target: image
                        property: "anchors.topMargin"
                        duration: 100
                    }
                }
            }
        },
        Transition {
            to: "activeScene"

            SequentialAnimation {
                NumberAnimation {
                    target: root
                    properties: "anchors.rightMargin"
                    duration: 250
                    easing.type: Easing.OutQuart
                }

                ParallelAnimation {
                    NumberAnimation {
                        target: image
                        property: "opacity"
                        duration: 200
                    }
                    NumberAnimation {
                        target: image
                        property: "anchors.topMargin"
                        duration: 100
                    }
                }
            }
        },
        Transition {
            to: "videoWallpaper"

            SequentialAnimation {
                NumberAnimation {
                    target: root
                    properties: "anchors.rightMargin"
                    duration: 250
                    easing.type: Easing.OutQuart
                }

                ParallelAnimation {
                    NumberAnimation {
                        target: image
                        property: "opacity"
                        duration: 200
                    }
                    NumberAnimation {
                        target: image
                        property: "anchors.topMargin"
                        duration: 100
                    }
                }
            }
        }
    ]
}
