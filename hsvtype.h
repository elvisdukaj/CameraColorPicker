#ifndef HSVTYPE_H
#define HSVTYPE_H

struct NormalizedHSV
{
	float h, s, v;
};

struct NormalizedHSVRange {
    enum RangeType { Internal, External };

	NormalizedHSV lower;
	NormalizedHSV upper;
    RangeType rangeType;
};

#endif // HSVTYPE_H
