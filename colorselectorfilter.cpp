#include "colorselectorfilter.h"
#include "colorselectorfilterrunnable.h"

QVideoFilterRunnable* ColorSelectorFilter::createFilterRunnable()
{
    return new ColorSelectorFilterRunnable(this);
}

