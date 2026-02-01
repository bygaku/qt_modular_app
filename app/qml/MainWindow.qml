import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1

import TimerModule 1.0

// Window: Main(Transparent).
Window {
    id: root
    visible: true

    title: qsTr("Widget Launcher")
    color: "yellow"
    width: 300; height: 200
    x: Screen.width - width - 50; y: Screen.height - height - 50

    flags: Qt.FramelessWindowHint   |
           Qt.WindowStaysOnTopHint  |
           Qt.WindowTransparentForInput

    SystemTrayIcon {
        id: tray
        visible: true
        icon.source: "qrc:/images/icon.png"

        onActivated: {
            root.showNormal()
            root.raise()
            root.requestActivate()
        }

        menu: Menu {
            MenuItem {
                text: qsTr("すべてのモジュールを最小化");
                onTriggered: root.showMinimized()
            }

            MenuItem {
                text: qsTr("終了");
                onTriggered: Qt.quit()
            }
        }
    }

    // Application background.
    // Item {
    //     id: transparent_background

    //     z: 0
    //     anchors.fill: parent

    //     MouseArea {
    //         anchors.fill: parent

    //         acceptedButtons: Qt.NoButton
    //         hoverEnabled: false
    //         propagateComposedEvents: true
    //         onPressed: mouse.accepted = false; onReleased: mouse.accepted = false; onWheel: wheel.accepted = false
    //     }
    // }
}
