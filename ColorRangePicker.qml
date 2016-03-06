import QtQuick 2.5

Item {
    property real maxRange: 1
    property real lowerValue: 0
    property real upperValue: 1

    property color color: "white"

    Thumb {
        id: lowerController
        anchors.fill: parent
        color: parent.color
    }
}
