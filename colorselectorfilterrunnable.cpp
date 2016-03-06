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



enum RangeType
{
    INTERNAL,
    EXTERNAL
};


struct HSVColorFilter
{
	HSVColorFilter( const cv::Vec3b lower,
					const cv::Vec3b upper,
                    RangeType rangeType = RangeType::INTERNAL)
		: lower(lower), upper(upper), rangeType(rangeType)
	{
    }

    static cv::Vec3b toOpenCV(const NormalizedHSV& hsv)
    {
        return cv::Vec3b(hsv.h / HUE_FACTOR,
                         hsv.s / SATURATION_FACTOR,
                         hsv.v / VALUE_FACTOR);
    }

    static NormalizedHSV fromOpenCV(const cv::Vec3b& hsv)
    {
        return {
                hsv[0] * HUE_FACTOR,
                hsv[1] * SATURATION_FACTOR,
                hsv[2] * VALUE_FACTOR
        };
    }

    cv::Vec3b lower = cv::Vec3b(0, 0, 0);
    cv::Vec3b upper = cv::Vec3b(180, 255, 255);
    RangeType rangeType = EXTERNAL;

private:
    static const float HUE_FACTOR;
    static const float SATURATION_FACTOR;
    static const float VALUE_FACTOR;
};

const float HSVColorFilter::HUE_FACTOR = 180.0f;
const float HSVColorFilter::SATURATION_FACTOR = 255.0f;
const float HSVColorFilter::VALUE_FACTOR = 255.0f;

//HSVColorFilter greenColorFilter(cv::Vec3b(30, 30, 30), cv::Vec3b(80, 255, 255));
//HSVColorFilter redColorFilter(cv::Vec3b(160, 50, 30), cv::Vec3b(30, 255, 255), RangeType::EXTERNAL);
//HSVColorFilter blueColorFilter(cv::Vec3b(70, 50, 30), cv::Vec3b(150, 255, 255));

HSVColorFilter g_colorFilter(cv::Vec3b(30, 30, 30), cv::Vec3b(80, 255, 255));

cv::Mat getMaskFromColorFilter(const cv::Mat& input, const HSVColorFilter& hsvFilter)
{
	cv::Mat result;
    if (hsvFilter.rangeType == RangeType::INTERNAL)
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

        const auto mask = getMaskFromColorFilter(toHsv(frame), g_colorFilter);

		cv::Mat frameToDisplay;
		cv::cvtColor(grayFrame, frameToDisplay, cv::COLOR_GRAY2BGR);
		frame.copyTo(frameToDisplay, mask);

		cv::cvtColor(frameToDisplay, frameRGBA, cv::COLOR_BGR2BGRA);

		input->unmap();
    }

    return *input;
}

void ColorSelectorFilterRunnable::setRangeRange(const NormalizedHSVRange& range)
{
    g_colorFilter.lower = HSVColorFilter::toOpenCV(range.lower);
    g_colorFilter.upper = HSVColorFilter::toOpenCV(range.upper);
}
