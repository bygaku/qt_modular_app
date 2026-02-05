import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

import Pomodoro 1.0

ApplicationWindow {
    id: pomo_window
    visible: true
    title: "Pomodoro Timer"

    width: 300
    height: 350
    x: Screen.width  - width  - 50
    y: Screen.height - height - 50

    flags: Qt.WindowStaysOnTopHint

    Pomodoro {
        id: pomodoro

        onFinished: {
            pomo_window.visible = true;
            pomo_window.raise();
            pomo_window.requestActivate();

            console.log("Time is up!")
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 20
        width: parent.width

        Text {
            Layout.alignment: Qt.AlignHCenter
            text: pomodoro.state == Pomodoro.BREAK ? "休憩中" : "集中タイム"
            font.pixelSize: 20
            color: "#666"
        }

        Text {
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 64
            font.family: "Monospace"
            text: {
                let m = Math.floor(pomodoro.currentTime / 60)
                let s = pomodoro.currentTime % 60
                return ("0" + m).slice(-2) + ":" + ("0" + s).slice(-2)
            }
        }

        Row {
            Layout.alignment: Qt.AlignHCenter
            spacing: 10

            Button {
                text: pomodoro.isRunning ? "STOP" : "START"
                onClicked: pomodoro.isRunning ? pomodoro.stop() : pomodoro.start()
                palette.buttonText: pomodoro.isRunning ? "red" : "green"
            }

            Button {
                text: "RESET"
                onClicked: pomodoro.reset()
            }
        }
    }
}
