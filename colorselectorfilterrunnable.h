#ifndef COLORSELECTORFILTERRUNNABLE_H
#define COLORSELECTORFILTERRUNNABLE_H

#include <QAbstractVideoFilter>

class ColorSelectorFilter;

struct NormalizedHSV
{
    float h, s, v;
};

struct NormalizedHSVRange {
    NormalizedHSV lower;
    NormalizedHSV upper;
};

class ColorSelectorFilterRunnable : public QVideoFilterRunnable
{
public:
    ColorSelectorFilterRunnable(ColorSelectorFilter* filter);

    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

    void setRangeRange(const NormalizedHSVRange& range);

private:
    ColorSelectorFilter* m_Filter;
    NormalizedHSVRange rangeFilter;
};


#endif // COLORSELECTORFILTERRUNNABLE_H
