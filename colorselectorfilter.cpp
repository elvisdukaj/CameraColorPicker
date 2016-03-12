#include "colorselectorfilterrunnable.h"
#include "colorselectorfilter.h"

ColorSelectorFilter::ColorSelectorFilter(QObject* parent)
    : QAbstractVideoFilter(parent), mRunnubleFiter(nullptr)
{
    mColorFilterRange.lower = NormalizedHSV{0.0f, 0.0f, 0.0f};
    mColorFilterRange.upper = NormalizedHSV{1.0f, 1.0f, 1.0f};
    mColorFilterRange.rangeType = NormalizedHSVRange::Internal;
}

ColorSelectorFilter::~ColorSelectorFilter()
{
}

QVideoFilterRunnable* ColorSelectorFilter::createFilterRunnable()
{
    mRunnubleFiter = std::make_unique<ColorSelectorFilterRunnable>();
    updateFilter();
    return mRunnubleFiter.get();
}

ColorSelectorFilterRunnable* ColorSelectorFilter::runnbleFilter() const
{
    return mRunnubleFiter.get();
}

void ColorSelectorFilter::onLowerValueChanged(float lowerVal)
{
    mColorFilterRange.lower = NormalizedHSV{lowerVal, 0.0f, 0.0f};
    updateFilter();
}

void ColorSelectorFilter::onUpperValueChanged(float upperVal)
{
    mColorFilterRange.upper = NormalizedHSV{upperVal, 1.0f, 1.0f};
    updateFilter();
}

void ColorSelectorFilter::onRangeTypeChanged(int rangeType)
{
    mColorFilterRange.rangeType = rangeType == ColorSelectorFilter::Internal ? NormalizedHSVRange::Internal : NormalizedHSVRange::External;
    updateFilter();
}

void ColorSelectorFilter::updateFilter()
{
    if (mRunnubleFiter)
        mRunnubleFiter->setColorRange(mColorFilterRange);
}
