import QtQuick 2.5
import QtGraphicalEffects 1.0

Rectangle {

    color: "transparent"
    border.color: "black"
    border.width: 1

    LinearGradient {
        anchors.fill: parent
        anchors.margins: 1

        y: parent.height / 2

        start: Qt.point(0, parent.height / 2);
        end: Qt.point(parent.width, parent.height / 2);

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
}
