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

    HSVRangeSlider {
        id: range

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: parent.height / 2
    }

    Text {
        id: lowerValue
        anchors.left: parent.left
        anchors.top: parent.top
        text: range.lowerValue.toFixed(2)
    }

    Text {
        id: upperValue
        anchors.right: parent.right
        anchors.top: parent.top
        text: range.upperValue.toFixed(2)
    }
}
