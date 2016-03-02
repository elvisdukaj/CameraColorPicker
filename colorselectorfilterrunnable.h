#ifndef COLORSELECTORFILTERRUNNABLE_H
#define COLORSELECTORFILTERRUNNABLE_H

#include <QAbstractVideoFilter>

class ColorSelectorFilter;

class ColorSelectorFilterRunnable : public QVideoFilterRunnable
{
public:
    ColorSelectorFilterRunnable(ColorSelectorFilter* filter);

    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

private:
    ColorSelectorFilter* m_Filter;
};


#endif // COLORSELECTORFILTERRUNNABLE_H
