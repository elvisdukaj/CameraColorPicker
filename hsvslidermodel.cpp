#include "hsvslidermodel.h"
#include "colorselectorfilterrunnable.h"
#include "colorselectorfilter.h"
#include <QDebug>


HSVSliderModel::HSVSliderModel(ColorSelectorFilter *filter)
	: mFilter(filter)
{
    qDebug() << this << ": ctor";
}

HSVSliderModel::~HSVSliderModel()
{
    qDebug() << this << ": dtor";
}

QObject *HSVSliderModel::colorFilter() const
{
    return mFilter;
}

void HSVSliderModel::setColorFilter(QObject *filter)
{
	mFilter = filter;
    updateFilter();
}

void HSVSliderModel::onLowerValueChanged(float lowerVal)
{
    mColorFilterRange.lower = NormalizedHSV{lowerVal, 0.0f, 0.0f};
	updateFilter();
}

void HSVSliderModel::onUpperValueChanged(float upperVal)
{
    mColorFilterRange.upper = NormalizedHSV{upperVal, 1.0f, 1.0f};
	updateFilter();
}

void HSVSliderModel::onRangeTypeChanged(int rangeType)
{
    mColorFilterRange.rangeType = rangeType == HSVSliderModel::Internal ? NormalizedHSVRange::Internal : NormalizedHSVRange::External;
    updateFilter();
}

void HSVSliderModel::onActived(bool)
{
    updateFilter();
}

void HSVSliderModel::updateFilter()
{
	if(mFilter)
    {
        auto runnubleFilter = ((ColorSelectorFilter*)mFilter)->runnbleFilter();
        if (runnubleFilter)
            runnubleFilter->setColorRange(mColorFilterRange);
    }
}
