#ifndef HSVTYPE_H
#define HSVTYPE_H

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

#endif // HSVTYPE_H
