#include "colorselectorfilterrunnable.h"
#include "colorselectorfilter.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

ColorSelectorFilterRunnable::
ColorSelectorFilterRunnable(ColorSelectorFilter *filter)
    : m_Filter( filter )
{
}

QVideoFrame ColorSelectorFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat&, QVideoFilterRunnable::RunFlags)
{
    if (input->isValid())
    {
        const auto handleType = input->handleType();
        const auto pixelFormat = input->pixelFormat();

        if ((handleType != QAbstractVideoBuffer::HandleType::NoHandle) ||
            (pixelFormat != QVideoFrame::PixelFormat::Format_RGB32 ))
            return *input;

        if (!input->map(QAbstractVideoBuffer::ReadOnly))
            return *input;

        cv::Mat frameRGBA(input->height(), input->width(), CV_8UC4, input->bits(), input->bytesPerLine());
        cv::Mat frame = frameRGBA.clone();
        input->unmap();

        frame.convertTo(frame, CV_8UC3);

        cv::flip(frame, frame, -1);


//        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGBA);


        cv::imshow("frame", frame);
        cv::imshow("frameRGBA", frameRGBA);


//        cv::imshow("frame", frame);
//        cv::imshow("frameRGBA", frameRGBA);
//        QImage image(frameRGBA.data, frameRGBA.cols, frameRGBA.rows, QImage::Format_RGB32);

        QImage image(frame.data, frameRGBA.cols, frameRGBA.rows, frameRGBA.step, QImage::Format_RGB32);
//        image.save("image.bmp");
        return QVideoFrame(image);
    }

    return *input;
}
