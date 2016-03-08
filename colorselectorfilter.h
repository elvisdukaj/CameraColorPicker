#ifndef COLORSELECTORFILTER_H
#define COLORSELECTORFILTER_H

#include <QAbstractVideoFilter>

class ColorSelectorFilterRunnable;

class ColorSelectorFilter : public QAbstractVideoFilter
{
public:
    QVideoFilterRunnable* createFilterRunnable() override;
	~ColorSelectorFilter();

	ColorSelectorFilterRunnable* runnbleFilter() const { return mRunnubleFiter; }

private:
    friend class ColorSelectorFilterRunnable;
	ColorSelectorFilterRunnable* mRunnubleFiter;
};

#endif // COLORSELECTORFILTER_H
