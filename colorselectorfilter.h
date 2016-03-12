#ifndef COLORSELECTORFILTER_H
#define COLORSELECTORFILTER_H

#include <QAbstractVideoFilter>
#include <memory>

class ColorSelectorFilterRunnable;

class ColorSelectorFilter : public QAbstractVideoFilter {
    Q_OBJECT

public:
    ColorSelectorFilter(QObject* parent = nullptr);
    ~ColorSelectorFilter();

    virtual QVideoFilterRunnable* createFilterRunnable() override;
    ColorSelectorFilterRunnable* runnbleFilter() const;

private:
    friend class ColorSelectorFilterRunnable;
    std::unique_ptr<ColorSelectorFilterRunnable> mRunnubleFiter;
};

#endif // COLORSELECTORFILTER_H
