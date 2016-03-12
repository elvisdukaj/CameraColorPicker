#include "colorselectorfilter.h"
#include "colorselectorfilterrunnable.h"
#include <QDebug>

ColorSelectorFilter::ColorSelectorFilter(QObject *parent)
    :QAbstractVideoFilter(parent)
{
    qDebug() << this << ": ctor";
}

ColorSelectorFilter::~ColorSelectorFilter()

{
    qDebug() << this << ": ctor";
}

QVideoFilterRunnable* ColorSelectorFilter::createFilterRunnable()
{
    mRunnubleFiter = std::make_unique<ColorSelectorFilterRunnable>();
    return mRunnubleFiter.get();
}

ColorSelectorFilterRunnable *ColorSelectorFilter::runnbleFilter() const
{
    return mRunnubleFiter.get();
}
