import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: slider

    Accessible.role: Accessible.Slider

    width: 100
    height: 100

    color: "transparent"

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right

        height: parent.height / 2
        y: parent.height / 4

        color: "transparent"
        border.color: "black"
        border.width: 2

        LinearGradient {
            anchors.fill: parent
            anchors.margins: 1
            y: parent.height / 4

            start: Qt.point(0, 0);
            end: Qt.point(parent.width, 0);

            gradient: Gradient {
                GradientStop {position: 0/6; color: Qt.rgba(1, 0, 0, 1)}
                GradientStop {position: 1/6; color: Qt.rgba(1, 1, 0, 1)}
                GradientStop {position: 2/6; color: Qt.rgba(0, 1, 0, 1)}
                GradientStop {position: 3/6; color: Qt.rgba(0, 1, 1, 1)}
                GradientStop {position: 4/6; color: Qt.rgba(0, 0, 1, 1)}
                GradientStop {position: 5/6; color: Qt.rgba(1, 0, 1, 1)}
                GradientStop {position: 6/6; color: Qt.rgba(1, 0, 0, 1)}
            }
        }

        ColorRangePicker {
            width: 10
            height: 30

            x: parent.width / 4 * 3
            y: parent.height / 5
            lineWidth: 2
        }
    }
}
