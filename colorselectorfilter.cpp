#include "colorselectorfilter.h"
#include "colorselectorfilterrunnable.h"
#include <QDebug>

ColorSelectorFilter::ColorSelectorFilter(QObject* parent)
    : QAbstractVideoFilter(parent), mRunnubleFiter(nullptr)
{
    qDebug() << this << ": ctor";
}

ColorSelectorFilter::~ColorSelectorFilter()
{
    qDebug() << this << ": dtor";
}

QVideoFilterRunnable* ColorSelectorFilter::createFilterRunnable()
{
    mRunnubleFiter = std::make_unique<ColorSelectorFilterRunnable>();
    return mRunnubleFiter.get();
}

ColorSelectorFilterRunnable* ColorSelectorFilter::runnbleFilter() const
{
    return mRunnubleFiter.get();
}
