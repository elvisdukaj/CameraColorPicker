#ifndef COLORSELECTORFILTERRUNNABLE_H
#define COLORSELECTORFILTERRUNNABLE_H

#include <QAbstractVideoFilter>
#include <memory>
#include "hsvtype.h"

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
