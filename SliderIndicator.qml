import QtQuick 2.5

Canvas {
    id: triangle
    antialiasing: true

    width: 60; height: 60

    property int triangleWidth: 60
    property int triangleHeight: 60
    property color strokeStyle:  "#ffffff"
    property color fillStyle: "#ffffff"
    property int lineWidth: 3
    property bool fill: false
    property bool stroke: true
    property real alpha: 1.0
    states: [
        State {
            name: "pressed"; when: ma1.pressed
            PropertyChanges { target: triangle; fill: true; }
        }
    ]

    onLineWidthChanged:requestPaint();
    onFillChanged:requestPaint();
    onStrokeChanged:requestPaint();

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
        ctx.moveTo(0, triangleHeight / 2 );
        ctx.lineTo(triangleWidth, triangleHeight);
        ctx.lineTo(triangleWidth, 0);
        ctx.closePath();

        if (triangle.fill)
            ctx.fill();
        if (triangle.stroke)
            ctx.stroke();
        ctx.restore();
    }
    MouseArea{
        id: ma1
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}

//import QtQuick 2.0

//Canvas {
//    id: root
//    // canvas size
//    width: 200; height: 200
//    // handler to override for drawing
//    onPaint: {
//        // get context to draw with
//        var ctx = getContext("2d")
//        // setup the stroke
//        ctx.lineWidth = 4
//        ctx.strokeStyle = "blue"
//        // setup the fill
//        ctx.fillStyle = "steelblue"
//        // begin a new path to draw
//        ctx.beginPath()
//        // top-left start point
//        ctx.moveTo(50,50)
//        // upper line
//        ctx.lineTo(150,50)
//        // right line
//        ctx.lineTo(150,150)
//        // bottom line
//        ctx.lineTo(50,150)
//        // left line through path closing
//        ctx.closePath()
//        // fill using fill style
//        ctx.fill()
//        // stroke using line width and stroke style
//        ctx.stroke()
//    }
//}
