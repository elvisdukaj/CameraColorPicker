import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true

    width: 800;
    height: 600

//    onWidthChanged: console.log("width now is ", width)
//    onHeightChanged: console.log("height now is ", height)

    MainForm {
        anchors.fill: parent
    }


}
