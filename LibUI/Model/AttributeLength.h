#pragma once
#include "Base/Object.h"

class AttributeLength : public Object
{
public:
	enum Type {
		TypeAuto,
		TypePixel,
		TypePercent,
	};
	AttributeLength();
	~AttributeLength();

	static SPtr<AttributeLength> Auto();
	static SPtr<AttributeLength> Pixel(uint32 pixel);
	static SPtr<AttributeLength> Percent(float percent);

	void SetAuto();
	void SetPixel(uint32 pixel);
	void SetPercent(float percent);

	bool IsAuto() const { return type_ == TypeAuto; }
	bool IsPixel() const { return type_ == TypePixel; }
	bool IsPercent() const { return type_ == TypePercent; }

	uint32 GetPixel() const { assert(IsPixel()); return pixel_; }
	float GetPercent() const { assert(IsPercent()); return percent_; }

	bool IsEqualAuto() const { return IsAuto(); }
	bool IsEqualPixel(uint32 pixel) const;
	bool IsEqualPercent(float percent) const;

	bool IsEqual(const AttributeLength* other) const;
private:
	Type type_;
	union {
		uint32 pixel_;
		float	percent_;
	};
};
