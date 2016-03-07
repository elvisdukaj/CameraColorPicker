import QtQuick 2.5

Item {
    id: rangeSlider
    property int thumbWidth: height

    property real lowerValue: lowerThumb.x  / (width - lowerThumb.width)
    property real upperValue: upperThumb.x / (width - upperThumb.width)

    Thumb {
        id: lowerThumb
        anchors.bottom: parent.bottom

        width: thumbWidth
        height: parent.height

        x: 0

        color: Qt.hsla(lowerValue, 1.0, 0.5, 1.0)

        MouseArea {
            anchors.fill: parent

            drag.target: parent;
            drag.axis: Drag.XAxis
            drag.minimumX: 0;
            drag.maximumX: upperThumb.x - width

        }
    }

    Thumb {
        id: upperThumb
        anchors.bottom: parent.bottom

        width: thumbWidth
        height: parent.height

        x: parent.width - width

        color: Qt.hsla(upperValue, 1.0, 0.5, 1.0)

        MouseArea {
            anchors.fill: parent

            drag.target: parent;
            drag.axis: Drag.XAxis
            drag.minimumX: lowerThumb.x + lowerThumb.width
            drag.maximumX: rangeSlider.width - width
        }
    }
}
