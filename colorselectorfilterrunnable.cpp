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

enum class HSVColorFilterRangeType
{
	INTERNAL,
	EXTERNAL
};

struct HSVColorFilter
{
	HSVColorFilter( const cv::Vec3b lower,
					const cv::Vec3b upper,
					HSVColorFilterRangeType rangeType = HSVColorFilterRangeType::INTERNAL)
		: lower(lower), upper(upper), rangeType(rangeType)
	{
	}

	cv::Vec3b lower = cv::Vec3b(0, 0, 0);
	cv::Vec3b upper = cv::Vec3b(180, 255, 255);
	HSVColorFilterRangeType rangeType = HSVColorFilterRangeType::EXTERNAL;
};

HSVColorFilter greenColorFilter(cv::Vec3b(30, 30, 30), cv::Vec3b(80, 255, 255));
HSVColorFilter redColorFilter(cv::Vec3b(160, 50, 30), cv::Vec3b(30, 255, 255), HSVColorFilterRangeType::EXTERNAL);
HSVColorFilter blueColorFilter(cv::Vec3b(70, 50, 30), cv::Vec3b(150, 255, 255));

cv::Mat getMaskFromColorFilter(const cv::Mat& input, const HSVColorFilter& hsvFilter)
{
	cv::Mat result;
	if (hsvFilter.rangeType == HSVColorFilterRangeType::INTERNAL)
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

		cv::cvtColor(frameRGBA, frame, cv::COLOR_BGRA2BGR);

		const auto grayFrame = toGrayScale(frame);
        const auto mask = getMaskFromColorFilter(toHsv(frame), blueColorFilter);

		cv::Mat frameToDisplay;
		cv::cvtColor(grayFrame, frameToDisplay, cv::COLOR_GRAY2BGR);
		frame.copyTo(frameToDisplay, mask);

//		cv::flip(frameToDisplay, frameToDisplay, 1);
		cv::cvtColor(frameToDisplay, frameRGBA, cv::COLOR_BGR2BGRA);

		input->unmap();
    }

    return *input;
}
