import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import "Components"

Window {
    id: window
    color: "#eeeeee"
    visible: true
    width: 1380
    height: 768

    Loader {
        id: pageLoader
        anchors {
            top: nav.bottom
            right: parent.right
            bottom: parent.bottom
            left: parent.left
        }
        source: "qrc:/qml/Components/Installed.qml"
//        onSourceChanged: pageLoaderAnim.running = true

//        SequentialAnimation {
//            id:pageLoaderAnim
//            running: true
//            NumberAnimation { target: pageLoader.item; property: "opacity"; from:0; to: 1; duration: 500 }
//            NumberAnimation { target: pageLoader.item; property: "y"; from: -100; to: 0; duration: 300 }
//        }

        Connections{
            target: pageLoader.item
            ignoreUnknownSignals: true
            onSetSidebaractiveItem: {
                if( sidebar.activeScreen == screenId && sidebar.state ==  "active"){
                    sidebar.state =  "inactive"
                } else {
                    sidebar.state =  "active"
                }

                sidebar.activeScreen = screenId

            }
        }
    }

    Sidebar {
        id: sidebar
        width:400
        anchors {
            top:nav.bottom
            right:parent.right
            bottom:parent.bottom
        }
    }

    Navigation {
        id: nav
        anchors {
            top: parent.top
            right: parent.right
            left: parent.left
        }
        onChangeTab: {
            pageLoader.setSource("qrc:/qml/Components/"+name+".qml")
            sidebar.state = "inactive"
        }

        onToggleMonitors: {
            monitors.state = monitors.state == "active" ? "inactive" : "active"
        }
    }

    Monitors {
        id: monitors
        state: "inactive"
        anchors.fill: pageLoader
        z:98
    }


}
