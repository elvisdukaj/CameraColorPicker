import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id: slider

    Accessible.role: Accessible.Slider

    property real lowerValue: 60
    property real upperVolue: 360
    property color centralColor;


    width: 100
    height: 100

    color: "transparent"

    LinearGradient {
        width: parent.width
        height: parent.height / 2

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

    SliderIndicator
    {
        anchors.centerIn: parent
    }
}
