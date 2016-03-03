import QtQuick 2.5

Canvas {
    id: triangle
    antialiasing: true

    width: 50; height: 50

    property color strokeStyle:  "#ffffff"
    property color fillStyle: "#ffffff"
    property int lineWidth: 3
    property bool fill: false
    property bool stroke: true
    property real alpha: 1.0

    states: [
        State {
            name: "pressed"; when: mouseArea.pressed
            PropertyChanges { target: triangle; fill: true; }
        }
    ]

    onLineWidthChanged: requestPaint();
    onFillChanged: requestPaint();
    onStrokeChanged: requestPaint();

    signal clicked()

    onPaint: {
        var ctx = getContext("2d");

        ctx.save();
        ctx.clearRect(0,0,triangle.width, triangle.height);
        ctx.strokeStyle = triangle.strokeStyle;
        ctx.lineWidth = triangle.lineWidth
        ctx.fillStyle = triangle.fillStyle
        ctx.globalAlpha = triangle.alpha
        ctx.lineJoin = "round";

        ctx.beginPath();
        ctx.moveTo(width / 2, height / 2 );
        ctx.lineTo(width, height);
        ctx.lineTo(0, height);
        ctx.closePath();

        if (triangle.fill)
            ctx.fill();
        if (triangle.stroke)
            ctx.stroke();
        ctx.restore();
    }
    MouseArea{
        id: mouseArea
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
