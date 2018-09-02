cmake_minimum_required(VERSION 3.5)

project(CameraColorPicker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick Multimedia REQUIRED)
find_package(OpenCV REQUIRED imgproc calib3d)

add_executable(${PROJECT_NAME}
    "colorselectorfilter.h"
    "colorselectorfilterrunnable.h"
    "hsvtype.h"
    "colorselectorfilter.cpp"
    "colorselectorfilterrunnable.cpp"
    "main.cpp"
    "qml.qrc"
    )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Quick
    Qt5::Multimedia
    ${OpenCV_LIBS}
)
