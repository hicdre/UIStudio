#include "stdafx.h"
#include "PropertyObject.h"


PropertyObject::PropertyObject()
{

}

PropertyObject::~PropertyObject()
{
	Clear();
}

PropertyValue* PropertyObject::GetProperty(const std::string& propertyName) const
{
	auto iter = value_maps_.find(propertyName);
	if (iter != value_maps_.end())
		return iter->second;
	return NULL;
}

void PropertyObject::SetProperty(const std::string& propertyName, own PropertyValue* value)
{
	auto iter = value_maps_.find(propertyName);
	if (iter != value_maps_.end()
		&& iter->second->IsEqual(value))
	{
			return;
	}
	value_maps_[propertyName] = value;
	EventPropertyChanged.Execute(GetSelf<PropertyObject>(), propertyName);
}

void PropertyObject::Clear()
{
	for (auto iter = value_maps_.begin(); iter != value_maps_.end(); iter++)
	{
		delete iter->second;
	}
	value_maps_.clear();
}
