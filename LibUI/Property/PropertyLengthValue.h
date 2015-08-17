#pragma once
#include "Property/PropertyValue.h"

class PropertyLengthValue : public Object
{
public:
	enum Type {
		Auto,
		Pixel,
		Percent,
	};
	PropertyLengthValue();
	~PropertyLengthValue();

	void SetAuto();
	void SetPixel(uint32_t pixel);
	void SetPercent(float percent);

	bool IsAuto() const { return type_ == Auto; }
	bool IsPixel() const { return type_ == Pixel; }
	bool IsPercent() const { return type_ == Percent; }

	uint32_t GetPixel() const { assert(IsPixel()); return pixel_; }
	float GetPercent() const { assert(IsPercent()); return percent_; }

	bool IsEqualAuto() const { return IsAuto(); }
	bool IsEqualPixel(uint32_t pixel) const;
	bool IsEqualPercent(float percent) const;
private:
	Type type_;
	union {
		uint32_t pixel_;
		float	percent_;
	};
};
