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

SPtr<AttributeLength> AttributeCollection::GetAttributeLength(const std::string& attributeName) const
{
	SPtr<AttributeValue> v = GetAttribute(attributeName);
	if (v->IsLengthValue())
		return v->GetObjectValue();
	return AttributeLength::Auto();
}

void AttributeCollection::SetAttributeBool(const std::string& attributeName, bool value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeInt(const std::string& attributeName, int value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeFloat(const std::string& attributeName, float value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeDouble(const std::string& attributeName, double value)
{
	SetAttribute(attributeName, new AttributeValue(value));
}

void AttributeCollection::SetAttributeLength(const std::string& attributeName, const SPtr<AttributeLength>& value)
{	
	SetAttribute(attributeName, new AttributeValue(value, AttributeTypeLength));
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
