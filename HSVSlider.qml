import QtQuick 2.5

Rectangle {
    id: slider
    width: 150
    height: 50

    color: "transparent"

    property alias lowerValue: range.lowerValue
    property alias upperValue: range.upperValue
    property bool isInternal: true

    HSVGradient {
        id: gradient

        y: 0
        anchors.horizontalCenter: parent.horizontalCenter

        height: parent.height / 3 * 2
        width: range.width - range.thumbWidth

        MouseArea {
            anchors.fill: parent

            onClicked: slider.isInternal = !slider.isInternal
        }
    }

    Rectangle {
        id: selectedZoneLeft

        visible: parent.isInternal

        y: 0
        x: range.thumbWidth / 2

        height: gradient.height
        width: range.lowerThumbX

        color: "#aaaaaaaa"
        border.color: "white"
    }

    Rectangle {
        id: innerSelectedZone

        visible: !parent.isInternal

        y: 0
        x: range.lowerThumbX + range.thumbWidth / 2

        height: gradient.height
        width: range.upperThumbX - x + range.thumbWidth / 2

        color: "#aaaaaaaa"
        border.color: "white"
    }

    Rectangle {
        id: selectedZoneRight
        visible: parent.isInternal

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
