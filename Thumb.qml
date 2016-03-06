import QtQuick 2.5

Item {
    property color color

    ThumbCanvas {
        anchors.fill: parent
        color: parent.color
    }
}
