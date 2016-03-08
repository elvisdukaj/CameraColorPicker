#include "hsvslidermodel.h"
#include "colorselectorfilterrunnable.h"
#include "colorselectorfilter.h"
#include <QDebug>


HSVSliderModel::HSVSliderModel(ColorSelectorFilter *filter)
	: mFilter(filter)
{
	qDebug() << "HSVSliderModel ctor [" << this << "]";
}

QObject *HSVSliderModel::colorFilter() const
{
	qDebug() << this << ": colorFilter -> mFilter " << mFilter;
	return mFilter;
}

void HSVSliderModel::setColorFilter(QObject *filter)
{
	qDebug() << this << ": setColorFilter <- mFilter:" << filter;
	mFilter = filter;
}

void HSVSliderModel::onLowerValueChanged(float lowerVal)
{
	mColorFilterRange.lower = NormalizedHSV{lowerVal * 360.0f, 0.0f, 0.0f};
	updateFilter();
}

void HSVSliderModel::onUpperValueChanged(float upperVal)
{
	mColorFilterRange.upper = NormalizedHSV{upperVal * 360.0f, 100.0f, 100.0f};
	updateFilter();
}

void HSVSliderModel::onRangeTypeChanged(HSVRangeType rangeType)
{
	mColorFilterRange.rangeType = rangeType;
	updateFilter();
}

void HSVSliderModel::updateFilter()
{
	qDebug() << "HSVSliderModel[" << this << "]: mRunnableFilter is " << mFilter;

	if(mFilter)
		((ColorSelectorFilter*)mFilter)->runnbleFilter()->setColorRange(mColorFilterRange);

}
