#include "stdafx.h"
#include "AttributeCollection.h"
#include "UIObject.h"

AttributeCollection::AttributeMap AttributeCollection::default_attribute_map_;



AttributeCollection::AttributeCollection(const SPtr<UIObject>& owner)
	: owner_(owner->GetWeak<UIObject>())
{

}

AttributeCollection::~AttributeCollection()
{

}

void AttributeCollection::InitDefaultMap()
{
	default_attribute_map_["x"] = new AttributeValue(new AttributeLength, AttributeTypeLength);
	default_attribute_map_["y"] = new AttributeValue(new AttributeLength, AttributeTypeLength);
	default_attribute_map_["width"] = new AttributeValue(new AttributeLength, AttributeTypeLength);
	default_attribute_map_["height"] = new AttributeValue(new AttributeLength, AttributeTypeLength);
	default_attribute_map_["visible"] = new AttributeValue(true);
}

void AttributeCollection::Clear()
{
	attribute_map_.clear();
}

bool AttributeCollection::HasAttribute(const std::string& attributeName) const
{
	return attribute_map_.count(attributeName) > 0;
}

SPtr<AttributeValue> AttributeCollection::GetAttribute(const std::string& attributeName) const
{
	{
		auto iter = attribute_map_.find(attributeName);
		if (iter != attribute_map_.end())
			return iter->second;
	}

	{
		auto iter = default_attribute_map_.find(attributeName);
		if (iter != attribute_map_.end())
			return iter->second;
	}

	return NULL;
}

void AttributeCollection::SetAttribute(const std::string& attributeName, const SPtr<AttributeValue>& value)
{
	auto iter = attribute_map_.find(attributeName);
	if (iter == attribute_map_.end())
	{
		attribute_map_[attributeName] = value;
		OnAttributeChanged(attributeName, value);
	}
	else
	{
		SPtr<AttributeValue> oldValue = iter->second;
		if (!oldValue->IsEqual(value.get()))
		{
			attribute_map_[attributeName] = value;
			OnAttributeChanged(attributeName, value);
		}		
	}
}

void AttributeCollection::SetAttributeIfDifferent(const std::string& attributeName, const SPtr<AttributeValue>& value, const std::function<void(void)>& OnChanged)
{
	auto iter = attribute_map_.find(attributeName);
	if (iter == attribute_map_.end())
	{
		attribute_map_[attributeName] = value;
		OnChanged();
		OnAttributeChanged(attributeName, value);
	}
	else
	{
		SPtr<AttributeValue> oldValue = iter->second;
		if (!oldValue->IsEqual(value.get()))
		{
			attribute_map_[attributeName] = value;
			OnChanged();
			OnAttributeChanged(attributeName, value);
		}
	}
}

void AttributeCollection::SetAttributeIfDifferent(const std::string& attributeName, const SPtr<AttributeValue>& value, const std::function<void(void)>& setCallback)
{

}

bool AttributeCollection::GetAttributeBool(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsBoolValue())
		return v->GetBoolValue();
	return false;
}

int32 AttributeCollection::GetAttributeInt(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsInt32Value())
		return v->GetInt32Value();
	return 0;
}

uint32 AttributeCollection::GetAttributeUInt(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsUInt32Value())
		return v->GetUInt32Value();
	return 0;
}

float AttributeCollection::GetAttributeFloat(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsFloatValue())
		return v->GetFloatValue();
	return 0;
}

double AttributeCollection::GetAttributeDouble(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsDoubleValue())
		return v->GetDoubleValue();
	return 0;
}

std::wstring AttributeCollection::GetAttributeUTF16(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsStringValue())
		return v->GetUTF16Value();
	return std::wstring();
}

std::string AttributeCollection::GetAttributeUTF8(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsStringValue())
		return v->GetUTF8Value();
	return std::string();
}

SPtr<AttributeLength> AttributeCollection::GetAttributeLength(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsLengthValue())
		return v->GetObjectValue();
	return AttributeLength::Auto();
}

SPtr<AttributePaint> AttributeCollection::GetAttributePaint(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->type() == AttributeTypePaint)
		return v->GetObjectValue();
	return AttributeColorPaint::NotSet();
}

void AttributeCollection::SetAttributeBool(const std::string& attributeName, bool value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeBoolIfDifferent(const std::string& attributeName, bool value, const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value), setCallback);
}

void AttributeCollection::SetAttributeInt(const std::string& attributeName, int value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeIntIfDifferent(const std::string& attributeName, int value, 
	const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value), setCallback);
}

void AttributeCollection::SetAttributeUInt(const std::string& attributeName, uint32 value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeUIntIfDifferent(const std::string& attributeName, uint32 value, const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value), setCallback);
}

void AttributeCollection::SetAttributeFloat(const std::string& attributeName, float value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeFloatIfDifferent(const std::string& attributeName, float value, const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value), setCallback);
}

void AttributeCollection::SetAttributeDouble(const std::string& attributeName, double value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeDoubleIfDifferent(const std::string& attributeName, double value, const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value), setCallback);
}

void AttributeCollection::SetAttributeString(const std::string& attributeName, const std::string& value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeString(const std::string& attributeName, const std::wstring& value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeStringIfDifferent(const std::string& attributeName, const std::string& value, const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value), setCallback);
}

void AttributeCollection::SetAttributeStringIfDifferent(const std::string& attributeName, const std::wstring& value, const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value), setCallback);
}

void AttributeCollection::SetAttributeLength(const std::string& attributeName, const SPtr<AttributeLength>& value)
{	
	SetAttribute(attributeName, new AttributeValue(value, AttributeTypeLength));
}

void AttributeCollection::SetAttributeLengthIfDifferent(const std::string& attributeName, const SPtr<AttributeLength>& value, const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value, AttributeTypeLength), setCallback);
}

void AttributeCollection::SetAttributePaint(const std::string& attributeName, const SPtr<AttributePaint>& value)
{
	SetAttribute(attributeName, new AttributeValue(value, AttributeTypePaint));
}

void AttributeCollection::SetAttributePaintIfDifferent(const std::string& attributeName, const SPtr<AttributePaint>& value, const std::function<void(void)>& setCallback)
{
	SetAttributeIfDifferent(attributeName, new AttributeValue(value, AttributeTypePaint), setCallback);
}

void AttributeCollection::RemoveAttribute(const std::string& attributeName)
{
	auto iter = attribute_map_.find(attributeName);
	if (iter == attribute_map_.end())
		return;
	attribute_map_.erase(iter);
	//移除属性后使用默认属性
	OnAttributeChanged(attributeName, GetAttribute(attributeName));
}

void AttributeCollection::OnAttributeChanged(const std::string& name, const SPtr<AttributeValue>& value)
{
	if (SPtr<UIObject>& owner = owner_.get())
	{
		EventAttributechanged.Execute(owner, new AttributeEventArgs(name, value));
	}
}
