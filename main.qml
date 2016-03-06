import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true

    width: 1280
    height: 720

    MainForm {
        anchors.fill: parent
    }

    HSVSlider {
        objectName: sliderObjName

        anchors.right: parent.right
        anchors.top: parent.top

        width: 150
        height: 30
        anchors.rightMargin: 7
        anchors.topMargin: 7
    }


}
