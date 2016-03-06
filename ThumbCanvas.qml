import QtQuick 2.5

Canvas {
    id: triangle

    antialiasing: true

    property color color: "#FF0000"
    property int lineWidth: 2

    onLineWidthChanged: requestPaint();

    onPaint: {
        var ctx = getContext("2d");

        ctx.save();
        ctx.clearRect(0,0,triangle.width, triangle.height);
        ctx.lineWidth = triangle.lineWidth
        ctx.fillStyle = triangle.color
        ctx.lineJoin = "round";

        ctx.beginPath();
        ctx.moveTo(width / 2, 0);
        ctx.lineTo(width, height / 2);
        ctx.lineTo(width, height);
        ctx.lineTo(0, height);
        ctx.lineTo(0, height / 2);
        ctx.closePath();

        ctx.fill();

        ctx.restore();
    }
}