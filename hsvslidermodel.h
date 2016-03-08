#ifndef HSVSLIDERMODEL_H
#define HSVSLIDERMODEL_H

#include <QObject>
#include "hsvtype.h"

class ColorSelectorFilter;

class HSVSliderModel : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QObject* colorFilter READ colorFilter WRITE setColorFilter)
	Q_ENUMS(HSVRangeType)

public:
	explicit HSVSliderModel(ColorSelectorFilter* filter = nullptr);

	QObject* colorFilter() const;
	void setColorFilter(QObject* filter);

public slots:
	void onLowerValueChanged(float lowerVal);
	void onUpperValueChanged(float upperVal);
	void onRangeTypeChanged(enum HSVRangeType rangeType);

private:
	void updateFilter();

private:
	QObject* mFilter;
	NormalizedHSVRange mColorFilterRange;
};

#endif // HSVSLIDERMODEL_H
