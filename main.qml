import QtQuick 2.5
import QtQuick.Window 2.2
import Elice.CameraColorSelector 1.0

Window {
    visible: true

    width: 1280
    height: 720

    MainForm {
        id: mainForm
        anchors.fill: parent

        onColorFilterActiveChanged: model.colorFilter = colorFilter
    }

    HSVSlider {
        id: slider

        anchors.right: parent.right
        anchors.top: parent.top

        width: 300
        height: 50
        anchors.rightMargin: 7
        anchors.topMargin: 7

        onLowerValueChanged: model.onLowerValueChanged(slider.lowerValue);
        onUpperValueChanged: model.onLowerValueChanged(slider.upperValue);
//        onIsInternalChanged: model.onLowerValueChanged();

        HSVSliderModel {
            id: model


        }
    }


}
