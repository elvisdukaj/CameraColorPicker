import QtQuick 2.5

Item {
    property real maxRange: 1
    property real lowerValue: 0
    property real upperValue: 1

    property color strokeStyle:  "#ffffff"
    property color fillStyle: "#ffffff"
    property int lineWidth: 3
    property bool fill: false
    property bool stroke: true
    property real alpha: 1.0

    MouseArea {
        anchors.fill: parent
    }

    TriangleCanvas {
        id: lowerController

        lineWidth: parent.lineWidth
    }

    TriangleCanvas {
        id: upperController

        lineWidth: parent.lineWidth
    }
}
