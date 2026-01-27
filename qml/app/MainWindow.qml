import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

// Window: Main(Transparent).
Window {
    id: main_window

    title: qsTr("Application - running")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.WindowTransparentForInput

    visible: true
    width: Screen.width; height: Screen.height
    color: "transparent"

    // Application background.
    Item {
        id: transparent_background

        z: 0
        anchors.fill: parent

        MouseArea {
            anchors.fill: parent

            acceptedButtons: Qt.NoButton
            hoverEnabled: false
            propagateComposedEvents: true
            onPressed: mouse.accepted = false; onReleased: mouse.accepted = false; onWheel: wheel.accepted = false
        }
    }
}
