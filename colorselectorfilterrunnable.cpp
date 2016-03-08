#include "colorselectorfilterrunnable.h"
#include "colorselectorfilter.h"
#include <opencv2/opencv.hpp>
#include <QDebug>

cv::Mat bgrToGrayScale(const cv::Mat& input)
{
	cv::Mat result;
	cv::cvtColor(input, result, cv::COLOR_BGR2GRAY);
	return result;
}

cv::Mat bgrToHsv(const cv::Mat& input)
{
	cv::Mat result;
	cv::cvtColor(input, result, cv::COLOR_BGR2HSV);
	return result;
}

struct HSVColorFilter
{
	HSVColorFilter( const cv::Vec3b lower,
					const cv::Vec3b upper,
					HSVRangeType rangeType = HSVRangeType::INTERNAL)
		: lower(lower), upper(upper), rangeType(rangeType)
	{
    }

    static cv::Vec3b toOpenCV(const NormalizedHSV& hsv)
    {
        return cv::Vec3b(hsv.h * HUE_FACTOR,
                         hsv.s * SATURATION_FACTOR,
                         hsv.v * VALUE_FACTOR);
    }

    static NormalizedHSV fromOpenCV(const cv::Vec3b& hsv)
    {
        return {
                hsv[0] / HUE_FACTOR,
                hsv[1] / SATURATION_FACTOR,
                hsv[2] / VALUE_FACTOR
        };
    }

    cv::Vec3b lower = cv::Vec3b(0, 0, 0);
	cv::Vec3b upper = cv::Vec3b(180, 255, 255);
	HSVRangeType rangeType = EXTERNAL;

private:
    static const float HUE_FACTOR;
    static const float SATURATION_FACTOR;
    static const float VALUE_FACTOR;
};

const float HSVColorFilter::HUE_FACTOR = 180.0f;
const float HSVColorFilter::SATURATION_FACTOR = 255.0f;
const float HSVColorFilter::VALUE_FACTOR = 255.0f;

cv::Mat getMaskFromColorFilter(const cv::Mat& input, const HSVColorFilter& hsvFilter)
{
	cv::Mat result;
	if (hsvFilter.rangeType == HSVRangeType::INTERNAL)
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

class ColorSelectorFilterRunnableImpl {
public:
	ColorSelectorFilterRunnableImpl(ColorSelectorFilter *filter)
		: mFilter(filter) , mColorFilter(cv::Vec3b(0, 0, 0), cv::Vec3b(180, 255, 255), HSVRangeType::INTERNAL)
	{
	}

	~ColorSelectorFilterRunnableImpl()
	{
		delete mFilter;
	}

	QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat&, QVideoFilterRunnable::RunFlags)
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

			const auto grayFrame = bgrToGrayScale(frame);

			const auto mask = getMaskFromColorFilter(bgrToHsv(frame), mColorFilter);

			cv::Mat frameToDisplay;
			cv::cvtColor(grayFrame, frameToDisplay, cv::COLOR_GRAY2BGR);
			frame.copyTo(frameToDisplay, mask);

			cv::cvtColor(frameToDisplay, frameRGBA, cv::COLOR_BGR2BGRA);

			input->unmap();
		}

		return *input;
	}

	void setRangeRange(const NormalizedHSVRange& range)
	{
		mColorFilter.lower  = HSVColorFilter::toOpenCV(range.lower);
		mColorFilter.upper = HSVColorFilter::toOpenCV(range.upper);
		mColorFilter.rangeType = range.rangeType;
	}

private:
	ColorSelectorFilter* mFilter;
	HSVColorFilter mColorFilter;
};

ColorSelectorFilterRunnable::ColorSelectorFilterRunnable(ColorSelectorFilter* filter)
	: mImpl(new ColorSelectorFilterRunnableImpl(filter))
{
}

ColorSelectorFilterRunnable::~ColorSelectorFilterRunnable()
{
	qDebug() << this << ": dctor";
}

QVideoFrame ColorSelectorFilterRunnable::run(
		QVideoFrame *input, const QVideoSurfaceFormat& surfaceFormat, QVideoFilterRunnable::RunFlags flags)
{
	return mImpl->run(input, surfaceFormat, flags);
}

void ColorSelectorFilterRunnable::setColorRange(const NormalizedHSVRange& range)
{
	return mImpl->setRangeRange(range);
}
