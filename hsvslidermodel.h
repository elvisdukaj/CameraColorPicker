#ifndef HSVSLIDERMODEL_H
#define HSVSLIDERMODEL_H

#include <QObject>
#include "hsvtype.h"

class ColorSelectorFilter;

class HSVSliderModel : public QObject
{
	Q_OBJECT
    Q_ENUMS(RangeType)
	Q_PROPERTY(QObject* colorFilter READ colorFilter WRITE setColorFilter)

public:
	explicit HSVSliderModel(ColorSelectorFilter* filter = nullptr);
    ~HSVSliderModel();

	QObject* colorFilter() const;
	void setColorFilter(QObject* filter);

    enum RangeType
    {
        Internal,
        External
    };

public slots:
	void onLowerValueChanged(float lowerVal);
	void onUpperValueChanged(float upperVal);
    void onRangeTypeChanged(int rangeType);
    void onActived(bool active);

private:
	void updateFilter();

private:
	QObject* mFilter;
	NormalizedHSVRange mColorFilterRange;
};

#endif // HSVSLIDERMODEL_H
