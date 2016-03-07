import QtQuick 2.5

Item {
    id: slider
    width: 150
    height: 50

    property alias lowerValue: range.lowerValue
    property alias upperValue: range.upperValue
    property alias gredientBorderColor: selectedGradientRegion.borderColor
    property alias isInternal: selectedGradientRegion.isInternal

    HSVGradient {
        id: gradient

        y: 0
        anchors.horizontalCenter: parent.horizontalCenter

        height: parent.height / 3 * 2
        width: range.width - range.thumbWidth

        HSVSelectedRegion {
            id: selectedGradientRegion

            anchors.fill: parent

            lowerThumbX: range.lowerThumbX
            upperThumbX: range.upperThumbX
        }

        MouseArea {
            anchors.fill: parent
            onClicked: selectedGradientRegion.isInternal = !selectedGradientRegion.isInternal
        }
    }

    HSVRangeSlider {
        id: range

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        height: parent.height / 2
    }
}
