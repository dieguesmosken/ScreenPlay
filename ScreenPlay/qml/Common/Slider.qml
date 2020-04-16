import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.2
import ScreenPlay 1.0

Item {
    id: sliderVolumeWrapperBottom
    height: 70

    property string headline: "dummyHeandline"
    property string iconSource: "qrc:/assets/icons/icon_volume.svg"
    property alias value: slider.value

    property alias from: slider.from
    property alias to: slider.to
    property alias stepSize: slider.stepSize

    Text {
        id: txtHeadline
        text: headline
        height: 20
        font.pointSize: 10
        font.family: ScreenPlay.settings.font
        color: "#626262"

        anchors {
            top: parent.top
            right: parent.right
            left: parent.left
        }
    }

    RowLayout {
        spacing: 30
        anchors {
            top: txtHeadline.bottom
            right: parent.right
            bottom: parent.bottom
            left: parent.left
        }

        Image {
            id: imgIcon
            width: 20
            height: 20
            source: iconSource
            sourceSize: Qt.size(20, 20)
            Layout.alignment: Qt.AlignVCenter
        }

        Slider {
            id: slider
            stepSize: 0.01
            from: 0
            value: 1
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            to: 1
        }

        Text {
            id: txtValue
            color: "#818181"
            text: Math.round(slider.value * 100) / 100
            Layout.alignment: Qt.AlignVCenter
            font.pointSize: 12
            font.italic: true
            verticalAlignment: Text.AlignVCenter
        }
    }
}
