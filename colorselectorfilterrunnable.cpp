#include "colorselectorfilterrunnable.h"
#include "colorselectorfilter.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

cv::Mat frame;

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
        frame = frameRGBA.clone();
        input->unmap();

        frame.convertTo(frame, CV_8UC3);

        cv::flip(frame, frame, -1);

        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGBA);


        QImage image(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        QVideoFrame vframe(image);
        return vframe;
    }

    return *input;
}
