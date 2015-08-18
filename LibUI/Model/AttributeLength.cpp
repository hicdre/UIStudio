#include "stdafx.h"
#include "AttributeLength.h"

AttributeLength::AttributeLength()
	: type_(TypeAuto)
{

}

AttributeLength::~AttributeLength()
{

}

SPtr<AttributeLength> AttributeLength::Auto()
{
	static SPtr<AttributeLength> defaultLength(new AttributeLength);
	return defaultLength;
}

SPtr<AttributeLength> AttributeLength::Pixel(uint32 pixel)
{
	SPtr<AttributeLength> length(new AttributeLength);
	length->SetPixel(pixel);
	return length;
}

SPtr<AttributeLength> AttributeLength::Percent(float percent)
{
	SPtr<AttributeLength> length(new AttributeLength);
	length->SetPercent(percent);
	return length;
}

void AttributeLength::SetAuto()
{
	type_ = TypeAuto;
}

void AttributeLength::SetPixel(uint32 pixel)
{
	type_ = TypePixel;
	pixel_ = pixel;
}

void AttributeLength::SetPercent(float percent)
{
	type_ = TypePercent;
	percent_ = percent;
}

bool AttributeLength::IsEqualPixel(uint32 pixel) const
{
	return IsPixel() && pixel_ == pixel;
}

bool AttributeLength::IsEqualPercent(float percent) const
{
	return IsPercent() && percent_ == percent;
}

bool AttributeLength::IsEqual(const AttributeLength* other) const
{
	if (type_ != other->type_)
		return false;
	return pixel_ == other->pixel_;
}

