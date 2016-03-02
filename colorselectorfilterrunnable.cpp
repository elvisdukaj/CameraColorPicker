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

        if (!input->map(QAbstractVideoBuffer::ReadWrite))
            return *input;

        assert (input->mappedBytes() == input->height() * input->bytesPerLine());

        cv::Mat frameRGBA(input->width(), input->height(), CV_8UC4, input->bits(), input->bytesPerLine());
        cv::Mat frame(input->width(), input->height(), CV_8UC3);
        cv::cvtColor(frameRGBA, frame, cv::COLOR_RGBA2BGR);
        input->unmap();

        cv::flip(frame, frame, 1);

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGBA);
        QImage image(frame.data, frame.cols, frame.rows, (int)frame.step, QImage::Format_RGB32);

//        QImage newImage(QSize(frame.rows, frame.cols), QImage::Format_RGB32);
        return QVideoFrame(frame.step * frame.cols, QSize(frame.rows, frame.cols), frame.step, input->pixelFormat());
    }

    return *input;
}
