import QtQuick 2.5
import QtQuick.Controls 1.4
import QtMultimedia 5.5
import Elice.CameraColorSelector 1.0

Item {
    Camera {
        id: camera

        viewfinder {
            resolution: "1280x720"
            maximumFrameRate: 30
        }
    }

    ColorFilter {
        id: colorFilter
        active: activeFilter.checked
    }

    VideoOutput {
        source: camera
        anchors.centerIn: parent;
        filters: [colorFilter]
    }

    GroupBox {
        anchors.top: parent.top
        anchors.left: parent.left

        CheckBox {
            id: activeFilter
            text: "Filter active"
            checked: false
        }
    }

    HSVSlider {
        anchors.right: parent.right
        anchors.top: parent.top

        width: 150
        height: 30
    }
}
