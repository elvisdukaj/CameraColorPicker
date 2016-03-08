#include "colorselectorfilter.h"

#define USE_QML_APPLICATION_ENGINE

#ifdef USE_QML_APPLICATION_ENGINE
#include <QtQuick>
#else
#include <QtGui/QGuiApplication>
#include <QtCore/QDir>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ColorSelectorFilter>("Elice.CameraColorSelector", 1, 0, "ColorFilter");

#ifdef USE_QML_APPLICATION_ENGINE
	QQmlApplicationEngine engine;
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
#else
	QQuickView viewer;
	viewer.setSource(QUrl("qrc:/main.qml"));
#endif

    return app.exec();
}
