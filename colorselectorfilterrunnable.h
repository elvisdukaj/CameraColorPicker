#ifndef COLORSELECTORFILTERRUNNABLE_H
#define COLORSELECTORFILTERRUNNABLE_H

#include <QAbstractVideoFilter>
#include <memory>

class ColorSelectorFilter;
class ColorSelectorFilterRunnableImpl;

enum HSVRangeType
{
	INTERNAL,
	EXTERNAL
};

struct NormalizedHSV
{
    float h, s, v;
};

struct NormalizedHSVRange {
	enum RangeType { INTERNAL, EXTERNAL };

    NormalizedHSV lower;
    NormalizedHSV upper;
	HSVRangeType rangeType;
};

class ColorSelectorFilterRunnable : public QVideoFilterRunnable
{
public:
    ColorSelectorFilterRunnable(ColorSelectorFilter* filter);

    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;
    void setRangeRange(const NormalizedHSVRange& range);

private:
	std::unique_ptr<ColorSelectorFilterRunnableImpl> mImpl;
};


#endif // COLORSELECTORFILTERRUNNABLE_H
