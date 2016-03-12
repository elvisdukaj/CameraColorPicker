#ifndef COLORSELECTORFILTER_H
#define COLORSELECTORFILTER_H

#include "hsvtype.h"
#include <QAbstractVideoFilter>
#include <memory>

class ColorSelectorFilterRunnable;

class ColorSelectorFilter : public QAbstractVideoFilter {
    Q_OBJECT
    Q_ENUMS(RangeType)

public:
    ColorSelectorFilter(QObject* parent = nullptr);
    ~ColorSelectorFilter();

    virtual QVideoFilterRunnable* createFilterRunnable() override;
    ColorSelectorFilterRunnable* runnbleFilter() const;

    enum RangeType
    {
        Internal,
        External
    };

public slots:
    void onLowerValueChanged(float lowerVal);
    void onUpperValueChanged(float upperVal);
    void onRangeTypeChanged(int rangeType);

private:
    void updateFilter();

private:
    std::unique_ptr<ColorSelectorFilterRunnable> mRunnubleFiter;
    NormalizedHSVRange mColorFilterRange;
};

#endif // COLORSELECTORFILTER_H
