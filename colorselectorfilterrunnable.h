#ifndef COLORSELECTORFILTERRUNNABLE_H
#define COLORSELECTORFILTERRUNNABLE_H

#include "hsvtype.h"
#include <QAbstractVideoFilter>
#include <memory>

class ColorSelectorFilterRunnableImpl;

class ColorSelectorFilterRunnable : public QVideoFilterRunnable
{
public:
    ColorSelectorFilterRunnable();
    ~ColorSelectorFilterRunnable();

    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;
	void setColorRange(const NormalizedHSVRange& range);

private:
    std::unique_ptr<ColorSelectorFilterRunnableImpl> mImpl;
};


#endif // COLORSELECTORFILTERRUNNABLE_H
