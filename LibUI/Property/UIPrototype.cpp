#include "stdafx.h"
#include "UIPrototype.h"
#include "PropertyObject.h"

UIPrototype::UIPrototype()
	: propertyWidth_(new PropertyLengthValue)
	, propertyHeight_(new PropertyLengthValue)
{

}

UIPrototype::~UIPrototype()
{

}

SPtr<PropertyLengthValue> UIPrototype::GetWidth()
{
	return propertyWidth_;
}

void UIPrototype::SetWidthAuto()
{
	PropertyLengthSetAuto("width", propertyWidth_.get());
}

void UIPrototype::SetWidthPixel(uint32_t pixel)
{
	PropertyLengthSetPixel("width", propertyWidth_.get(), pixel);
}

void UIPrototype::SetWidthPercent(float percent)
{
	PropertyLengthSetPercent("width", propertyWidth_.get(), percent);
}

SPtr<PropertyLengthValue> UIPrototype::GetHeight()
{
	return propertyHeight_;
}

void UIPrototype::SetHeightAuto()
{
	PropertyLengthSetAuto("height", propertyHeight_.get());
}

void UIPrototype::SetHeightPixel(uint32_t pixel)
{
	PropertyLengthSetPixel("height", propertyHeight_.get(), pixel);
}

void UIPrototype::SetHeightPercent(float percent)
{
	PropertyLengthSetPercent("height", propertyHeight_.get(), percent);
}

void UIPrototype::OnPropertyChanged(const std::string& name)
{
	EventPropertyChanged.Execute(GetSelf<UIPrototype>(), name);
}

void UIPrototype::PropertyLengthSetAuto(const std::string& name, PropertyLengthValue* val)
{
	if (val->IsEqualAuto())
		return;
	val->SetAuto();
	OnPropertyChanged(name);
}

void UIPrototype::PropertyLengthSetPixel(const std::string& name, PropertyLengthValue* val, uint32_t pixel)
{
	if (val->IsEqualPixel(pixel))
		return;
	val->SetPixel(pixel);
	OnPropertyChanged(name);
}

void UIPrototype::PropertyLengthSetPercent(const std::string& name, PropertyLengthValue* val, float percent)
{
	if (val->IsEqualPercent(percent))
		return;
	val->SetPercent(percent);
	OnPropertyChanged(name);
}

