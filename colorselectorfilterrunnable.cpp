#include "colorselectorfilterrunnable.h"
#include "colorselectorfilter.h"
#include <opencv2/opencv.hpp>
#include <QDebug>


cv::Mat toGrayScale(const cv::Mat& input)
{
	cv::Mat result;
	cv::cvtColor(input, result, cv::COLOR_BGR2GRAY);
	return result;
}

cv::Mat toHsv(const cv::Mat& input)
{
	cv::Mat result;
	cv::cvtColor(input, result, cv::COLOR_BGR2HSV);
	return result;
}

struct HSVColorFilter
{
	HSVColorFilter( const cv::Vec3b lower, const cv::Vec3b upper, bool isInternal = true)
		: lower(lower), upper(upper), isInternal(isInternal)
	{
	}

	cv::Vec3b lower = cv::Vec3b(0, 0, 0);
	cv::Vec3b upper = cv::Vec3b(180, 255, 255);
	bool isInternal = true;
};

HSVColorFilter greenColorFilter(cv::Vec3b(30, 30, 30), cv::Vec3b(90, 255, 255));

cv::Mat getMaskFromColorFilter(const cv::Mat& input, const HSVColorFilter& hsvFilter)
{
	cv::Mat result;
	if (hsvFilter.isInternal)
	{
		cv::inRange(input, hsvFilter.lower, hsvFilter.upper, result);
	}
	else
	{
		cv::Mat lowerRange, upperRange;

		cv::Vec3b toStart(180, hsvFilter.upper[1], hsvFilter.upper[2]);
		cv::inRange(input, hsvFilter.lower, toStart, lowerRange);

		cv::Vec3b fromStart(1, hsvFilter.lower[1], hsvFilter.lower[2]);
		cv::inRange(input, fromStart, hsvFilter.upper, upperRange);

		result = lowerRange + upperRange;
	}

	return result;
}

ColorSelectorFilterRunnable::
ColorSelectorFilterRunnable(ColorSelectorFilter *filter)
    : m_Filter( filter )
{
}

QVideoFrame ColorSelectorFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat&, QVideoFilterRunnable::RunFlags)
{
    if (input->isValid())
    {
		if ((input->handleType() != QAbstractVideoBuffer::HandleType::NoHandle) ||
			(input->pixelFormat() != QVideoFrame::PixelFormat::Format_RGB32 ))
            return *input;

		if (!input->map(QAbstractVideoBuffer::ReadWrite))
            return *input;

        cv::Mat frameRGBA(input->height(), input->width(), CV_8UC4, input->bits(), input->bytesPerLine());
		cv::Mat frame;

		cv::cvtColor(frameRGBA, frame, cv::COLOR_RGBA2BGR);

		const auto grayFrame = toGrayScale(frame);
		const auto mask = getMaskFromColorFilter(toHsv(frame), greenColorFilter);

		cv::Mat frameToDisplay;
		cv::cvtColor(grayFrame, frameToDisplay, cv::COLOR_GRAY2BGR);
		frame.copyTo(frameToDisplay, mask);

		cv::flip(frame, frame, 1);

		cv::cvtColor(frameToDisplay, frameRGBA, cv::COLOR_BGR2RGBA);

		input->unmap();
    }

    return *input;
}
