#include "stdafx.h"
#include "PropertyObject.h"


PropertyObject::PropertyObject()
{

}

PropertyObject::~PropertyObject()
{	
}

const PropertyValue* PropertyObject::GetProperty(const std::string& propertyName) const
{
	const PropertyValue* current_value;
	if (!property_dict_.Get(propertyName, &current_value))
		return NULL;
	return current_value;
}

void PropertyObject::SetProperty(const std::string& propertyName, own PropertyValue* value)
{
	PropertyValue* current_value;
	if (!property_dict_.Get(propertyName, &current_value)
		|| !current_value->IsEqual(value)) {

		property_dict_.Set(propertyName, value);
		OnPropertyChanged(propertyName);
	}
	else {
		delete value;
	}	
}

void PropertyObject::OnPropertyChanged(const std::string& name)
{
	EventPropertyChanged.Execute(GetSelf<PropertyObject>(), name);
}

