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
    delete mRunnubleFiter;
}

QVideoFilterRunnable* ColorSelectorFilter::createFilterRunnable()
{
    mRunnubleFiter = new ColorSelectorFilterRunnable();
    return mRunnubleFiter;
}

ColorSelectorFilterRunnable *ColorSelectorFilter::runnbleFilter() const
{
    return mRunnubleFiter;
}
