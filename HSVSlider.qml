import QtQuick 2.5

Rectangle {
    width: 150
    height: 50

    color: "transparent"

    property alias lowerValue: range.lowerValue
    property alias upperValue: range.upperValue

    HSVGradient {
        id: gradient

        y: 0
        anchors.horizontalCenter: parent.horizontalCenter

        height: parent.height / 3 * 2
        width: range.width - range.thumbWidth
    }

    Rectangle {
        id: selectedZoneLeft

        y: 0
        x: range.thumbWidth / 2

        height: gradient.height
        width: range.lowerThumbX

        color: "#aaaaaaaa"
        border.color: "white"
    }

    Rectangle {
        id: selectedZoneRight

        y: 0
        x: range.upperThumbX + (range.thumbWidth / 2)

        height: gradient.height
        width: gradient.width - x + range.thumbWidth / 2

        color: "#aaaaaaaa"
        border.color: "white"
    }

    HSVRangeSlider {
        id: range

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: parent.height / 2
    }
}
