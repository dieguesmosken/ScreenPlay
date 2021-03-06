import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Controls 2.14 as QQC
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.14
import ScreenPlay 1.0

Item {
    id: root
    height: 55
    width: 150

    state: {
        if (textField.text.length > 0) {
            return "containsTextEditingFinished"
        } else {
            return ""
        }
    }

    signal editingFinished
    onEditingFinished: {
        if (!root.required)
            return
    }

    property bool required: false
    property bool dirty: false
    property alias text: textField.text
    property alias placeholderText: txtPlaceholder.text

    Text {
        id: txtPlaceholder
        text: qsTr("Label")
        font.family: ScreenPlay.settings.font
        color: Material.primaryTextColor
        opacity: .4
        font.pointSize: 11
        font.weight: Font.Medium
        anchors {
            top: parent.top
            topMargin: 15
            left: parent.left
            leftMargin: 10
        }
    }

    Timer {
        id: timerSaveDelay
        interval: 1000
        onTriggered: root.editingFinished()
    }

    QQC.TextField {
        id: textField
        font.family: ScreenPlay.settings.font
        color: Material.secondaryTextColor
        width: parent.width
        Keys.onEscapePressed: resetState()
        onTextEdited: {
            timerSaveDelay.start()
            root.dirty = true
        }
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        onEditingFinished: {
            resetState()
            if (textField.text.length > 0) {
                root.state = "containsTextEditingFinished"
            }
        }

        function resetState() {
            if (textField.text.length === 0) {
                root.state = ""
            }
            textField.focus = false
        }

        onPressed: {
            root.state = "containsText"
        }
    }

    Text {
        id: requiredText
        text: qsTr("*Required")
        visible: root.required
        font.family: ScreenPlay.settings.font
        color: Material.secondaryTextColor
        anchors {
            top: textField.bottom
            right: textField.right
        }
    }

    states: [
        State {
            name: ""
            PropertyChanges {
                target: txtPlaceholder
                font.pointSize: 11
                color: Material.secondaryTextColor

                anchors.topMargin: 15
                anchors.leftMargin: 10
            }
        },
        State {
            name: "containsText"
            PropertyChanges {
                target: txtPlaceholder
                font.pointSize: 8
                opacity: 1
                color: Material.accentColor

                anchors.topMargin: 0
                anchors.leftMargin: 0
            }
        },
        State {
            name: "containsTextEditingFinished"
            PropertyChanges {
                target: txtPlaceholder
                font.pointSize: 8
                color: Material.secondaryTextColor
                opacity: 0.4

                anchors.topMargin: 0
                anchors.leftMargin: 0
            }
        }
    ]
    transitions: [
        Transition {
            from: ""
            to: "containsText"
            reversible: true
            PropertyAnimation {
                target: txtPlaceholder
                duration: 150
                easing.type: Easing.InOutQuart
                properties: "font.pointSize,anchors.topMargin,anchors.leftMargin,opacity,color"
            }
        },
        Transition {
            from: "containsText"
            to: "containsTextEditingFinished"
            reversible: true
            PropertyAnimation {
                target: txtPlaceholder
                duration: 150
                easing.type: Easing.OutSine
                properties: "color,opacity"
            }
        }
    ]
}
