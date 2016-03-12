import QtQuick 2.0
import Elice.CameraColorSelector 1.0

Item {
    property bool isInternal: true
    property int rangeType: HSVSliderModel.Internal

    property color borderColor: "lightgray"

    property int lowerThumbX
    property int upperThumbX

    Rectangle {
        id: selectedZoneLeft

        visible: parent.isInternal

        y: 0
        x: 0

        height: parent.height
        width: lowerThumbX

        color: "#aaaaaaaa"
        border.color: parent.borderColor
    }

    Rectangle {
        id: selectedZoneRight
        visible: parent.isInternal

        y: 0
        x: upperThumbX

        height: parent.height
        width: parent.width - x

        color: "#aaaaaaaa"
        border.color: parent.borderColor
    }

    Rectangle {
        id: innerSelectedZone

        visible: !parent.isInternal

        y: 0
        x: lowerThumbX

        height: parent.height
        width: upperThumbX - x

        color: "#aaaaaaaa"
        border.color: parent.borderColor
    }
}
