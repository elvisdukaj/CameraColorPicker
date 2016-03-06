import QtQuick 2.0

Rectangle {
    id: slider

    Accessible.role: Accessible.Slider

    width: 100;
    height: 50

    border.color: "black"
    color: "transparent"

    HSVGradient {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: parent.height / 4 * 3
    }

    Thumb {
        id: lowerThumb
        width: 10; height: parent.height / 2
        anchors.bottom: parent.bottom
        color: "white"

        MouseArea {
              anchors.fill: parent
              drag.target: parent;
              drag.axis: Drag.XAxis
              drag.minimumX: 0;
              drag.maximumX: upperThumb.x - lowerThumb.width
        }
    }

    Thumb {
        id: upperThumb
        width: 10; height: parent.height / 2
        anchors.bottom: parent.bottom
        x: parent.width - width
        color: "black"

        MouseArea {
              anchors.fill: parent
              drag.target: parent;
              drag.axis: Drag.XAxis
              drag.minimumX: lowerThumb.x + lowerThumb.width;
              drag.maximumX: slider.width - upperThumb.width
        }
    }
}
