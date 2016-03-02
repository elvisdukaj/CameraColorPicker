#ifndef COLORSELECTORFILTER_H
#define COLORSELECTORFILTER_H

#include <QAbstractVideoFilter>

class ColorSelectorFilter : public QAbstractVideoFilter
{
public:
    QVideoFilterRunnable* createFilterRunnable() override;

private:
    friend class ColorSelectorFilterRunnable;
};

#endif // COLORSELECTORFILTER_H
