import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2
import ScreenPlay 1.0

Item {
    id: settingsBool
    property string headline: "Headline"
    property string description: "Lorem ipsum dolor sit amet, consectetuer adipiscing elit."
    property bool isChecked: false
    property bool available: true
    onAvailableChanged: {
        if(!available){
            settingsBool.opacity = .5
            radioButton.enabled = false
        } else {
            settingsButton.opacity = 1
            radioButton.enabled = true
        }
    }
    signal checkboxChanged(bool checked)

    height: 50 +txtDescription.paintedHeight
    width: parent.width

    Text {
        id: txtHeadline
        color: "#5D5D5D"
        text: settingsBool.headline
        font.family: ScreenPlay.settings.font
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        anchors{
            top:parent.top
            topMargin: 6
            left:parent.left
            leftMargin: 20

        }

        font.pointSize: 12
    }

    Text {
        id: txtDescription
        text: settingsBool.description
        wrapMode: Text.WordWrap
        color: "#B5B5B5"
        font.family: ScreenPlay.settings.font
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pointSize: 10

        anchors{
            top:txtHeadline.bottom
            topMargin: 6
            left:parent.left
            leftMargin: 20
            right:radioButton.left
            rightMargin: 20
        }
    }

    CheckBox {
        id: radioButton
        anchors {
            right: parent.right
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }

        checked: settingsBool.isChecked
        onCheckedChanged: {
            if(radioButton.checkState === Qt.Checked){
                checkboxChanged(true)
            } else {
                checkboxChanged(false)
            }
        }
    }
}
