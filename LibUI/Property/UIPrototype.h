#pragma once
#include "Property/PropertyLengthValue.h"
#include "Delegate/Delegate.h"

class PropertyObject;

class UIPrototype : public Object
{
public:
	UIPrototype();
	~UIPrototype();	

	SPtr<PropertyLengthValue> GetWidth();
	void SetWidthAuto();
	void SetWidthPixel(uint32_t pixel);
	void SetWidthPercent(float percent);

	SPtr<PropertyLengthValue> GetHeight();
	void SetHeightAuto();
	void SetHeightPixel(uint32_t pixel);
	void SetHeightPercent(float percent);

	Event<void(const SPtr<UIPrototype>&, const std::string&)> EventPropertyChanged;
protected:
	void OnPropertyChanged(const std::string& name);

	void PropertyLengthSetAuto(const std::string& name, PropertyLengthValue* val);
	void PropertyLengthSetPixel(const std::string& name, PropertyLengthValue* val, uint32_t pixel);
	void PropertyLengthSetPercent(const std::string& name, PropertyLengthValue* val, float percent);
	SPtr<PropertyLengthValue> propertyWidth_;
	SPtr<PropertyLengthValue> propertyHeight_;
};
