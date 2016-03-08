#include "colorselectorfilter.h"
#include "colorselectorfilterrunnable.h"
#include <QDebug>

QVideoFilterRunnable* ColorSelectorFilter::createFilterRunnable()
{
	mRunnubleFiter = new ColorSelectorFilterRunnable(this);
	qDebug() << this << "createFilterRunnable; mRunnubleFiter is " << mRunnubleFiter;
	return mRunnubleFiter;
}

ColorSelectorFilter::~ColorSelectorFilter()
{
	qDebug() << this << ": dctor";
	delete mRunnubleFiter;
}
