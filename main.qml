import QtQuick 2.5
import QtQuick.Window 2.2
import Elice.CameraColorSelector 1.0

Window {
    visible: true

    width: 1280
    height: 720

    MainForm {
        id: form
        anchors.fill: parent
    }

    HSVSlider {
        id: slider

        anchors.right: parent.right
        anchors.top: parent.top

        width: 300
        height: 50
        anchors.rightMargin: 7
        anchors.topMargin: 7

        onLowerValueChanged: form.filter.onLowerValueChanged(slider.lowerValue)
        onUpperValueChanged: form.filter.onUpperValueChanged(slider.upperValue)
        onRangeTypeChanged: form.filter.onRangeTypeChanged(slider.rangeType)
    }
}
