import QtQuick 2.5
import QtQuick.Controls 1.4
import QtMultimedia 5.5
import Elice.CameraColorSelector 1.0

Item {
    property alias filter: colorFilter

    Camera {
        id: camera

        viewfinder {
            resolution: "1280x720"
            maximumFrameRate: 30
        }
    }

    ColorSelectorFilter {
        id: colorFilter
    }

    VideoOutput {
        id: videoOutput

        source: camera
        anchors.centerIn: parent;
        filters: [colorFilter]
    }
}
