import QtQuick 2.9
import QtGraphicalEffects 1.0

Rectangle {
    id: rect
    color: background
    radius: cornerRadius

    property color background: "transparent"
    property real cornerRadius: 0
    // Width of the Sidebar or Space that should be used
    property real availableWidth: 0
    property real availableHeight: 0
    property int activeMonitorIndex: 0
    property string activeMonitorID: "empty"

    function setActiveMonitorIndex(newIndex) {
        activeMonitorIndex = newIndex
        activeMonitorID = rp.itemAt(newIndex).monitorID
        for (var i = 0; i < rp.count; i++) {
            if (i === newIndex) {
                rp.itemAt(i).isSelected = true
            } else {
                rp.itemAt(i).isSelected = false
            }
        }
    }

    Component.onCompleted: {
        resize()
    }

    Connections {
        target: monitorListModel
        onMonitorReloadCompleted: {
            resize()
        }
    }

    function resize() {
            //  Absolute availableVirtualGeometry
            var absoluteDesktopSize = monitorListModel.getAbsoluteDesktopSize()
            var isWidthGreaterThanHeight = false
            var windowsDelta = 0

            if (absoluteDesktopSize.width < absoluteDesktopSize.height) {
                windowsDelta = absoluteDesktopSize.width / absoluteDesktopSize.height
                isWidthGreaterThanHeight = false
            } else {
                windowsDelta = absoluteDesktopSize.height / absoluteDesktopSize.width
                isWidthGreaterThanHeight = true
            }

            var dynamicHeight = availableWidth * windowsDelta
            var dynamicWidth = availableHeight * windowsDelta


            // Delta (height/width)
            var monitorHeightRationDelta = 0
            var monitorWidthRationDelta = 0

            if (isWidthGreaterThanHeight) {
                monitorHeightRationDelta = dynamicHeight / absoluteDesktopSize.height
                monitorWidthRationDelta = availableWidth / absoluteDesktopSize.width
            } else {
                monitorHeightRationDelta = availableHeight / absoluteDesktopSize.height
                monitorWidthRationDelta = dynamicWidth / absoluteDesktopSize.width
            }

            for (var i = 0; i < rp.count; i++) {
                rp.itemAt(i).index = i
                rp.itemAt(i).height = rp.itemAt(i).height * monitorHeightRationDelta
                rp.itemAt(i).width = rp.itemAt(i).width * monitorWidthRationDelta
                rp.itemAt(i).x = rp.itemAt(i).x * monitorWidthRationDelta
                rp.itemAt(i).y = rp.itemAt(i).y * monitorHeightRationDelta
            }
    }

    Repeater {
        id: rp
        anchors.fill: parent
        anchors.centerIn: parent
        model: monitorListModel

        delegate: MonitorSelectionItem {
            id: delegate
            height: monitorAvailableGeometry.height
            width: monitorAvailableGeometry.width
            x: monitorAvailableGeometry.x
            y: monitorAvailableGeometry.y
            monitorManufacturer:  monitorManufacturer
            monitorName: monitorName
            monitorModel: monitorModel
            monitorSize: monitorAvailableGeometry
            monitorID: monitorID
            index: index

            Connections {
                target: delegate
                onMonitorSelected: {
                    setActiveMonitorIndex(index)
                }
            }

        }
    }
}
