import QtQuick 2.5

Item {
    property color color: "red";

    ThumbCanvas {
        anchors.fill: parent
        color: parent.color
    }
}
