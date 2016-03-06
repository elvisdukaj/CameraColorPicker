import QtQuick 2.5

Rectangle {
    width: 150
    height: 50

    color: "transparent"

    HSVGradient {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        height: parent.height / 3 * 2
    }

    HSVRangeSlider {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: parent.height / 3 * 2
    }
}
