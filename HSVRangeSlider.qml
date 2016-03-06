import QtQuick 2.5

Item {
    property int thumbWidth: 10

    property real lowerValue: (lowerThumb.x - lowerThumb.width / 2) / width
    property real upperValue: (upperThumb.x - upperThumb.width / 2) / width

    Thumb {
        id: lowerThumb
        anchors.bottom: parent.bottom

        width: thumbWidth
        height: parent.height / 2

        x: 0

        color: Qt.hsla(lowerValue, 1.0, 0.5, 1.0)

        MouseArea {
            anchors.fill: parent
            drag.target: parent;
            drag.axis: Drag.XAxis
            drag.minimumX: 0;
            drag.maximumX: upperThumb.x - upperThumb.width
        }
    }

    Thumb {
        id: upperThumb
        anchors.bottom: parent.bottom

        width: thumbWidth
        height: parent.height / 2

        x: parent.width - width

        color: Qt.hsla(upperValue, 1.0, 0.5, 1.0)

        MouseArea {
            anchors.fill: parent
            drag.target: parent;
            drag.axis: Drag.XAxis
            drag.minimumX: lowerThumb.x + lowerThumb.width;
            drag.maximumX: slider.width - upperThumb.width
        }
    }
}
