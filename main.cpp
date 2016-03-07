#include "colorselectorfilter.h"
#include <QtQuick>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ColorSelectorFilter>("Elice.CameraColorSelector", 1, 0, "ColorFilter");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
