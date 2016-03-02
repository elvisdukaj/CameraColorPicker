TEMPLATE = app

QT += qml quick multimedia
CONFIG += c++11

SOURCES += main.cpp \
    colorselectorfilter.cpp \
    colorselectorfilterrunnable.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

win32 {
    INCLUDEPATH += $(OPENCV310_ROOT)/include
}

win32-msvc2015 {

    LIBS += -L$(OPENCV310_ROOT)/x64/vc14/lib

    CONFIG(debug, debug|release) {
        LIBS += -lopencv_world310d
    } else {
        LIBS += -lopencv_world310
    }
}

HEADERS += \
    colorselectorfilter.h \
    colorselectorfilterrunnable.h