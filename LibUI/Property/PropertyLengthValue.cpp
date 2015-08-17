#include "stdafx.h"
#include "PropertyLengthValue.h"

PropertyLengthValue::PropertyLengthValue()
	: type_(Auto)
{

}

PropertyLengthValue::~PropertyLengthValue()
{

}

void PropertyLengthValue::SetAuto()
{
	type_ = Auto;
}

void PropertyLengthValue::SetPixel(uint32_t pixel)
{
	type_ = Pixel;
	pixel_ = pixel;
}

void PropertyLengthValue::SetPercent(float percent)
{
	type_ = Percent;
	percent_ = percent;
}

bool PropertyLengthValue::IsEqualPixel(uint32_t pixel) const
{
	return IsPixel() && pixel_ == pixel;
}

bool PropertyLengthValue::IsEqualPercent(float percent) const
{
	return IsPercent() && percent_ == percent;
}

