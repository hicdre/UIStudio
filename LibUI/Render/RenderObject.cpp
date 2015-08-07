#include "stdafx.h"
#include "RenderObject.h"
#include "Property/PropertyObject.h"

RenderObject::RenderObject()
{

}

RenderObject::~RenderObject()
{

}

void RenderObject::Render()
{
	//not implment
}

void RenderObject::Attatch(const SPtr<PropertyObject>& object)
{
	propertyObject_.reset(object);
	object->EventPropertyChanged.AddW(GetWeak<RenderObject>(),
		&RenderObject::OnPropertyChangedInternal);
}

void RenderObject::Detach()
{
	propertyObject_.reset();
}

SPtr<PropertyObject> RenderObject::GetPropertyObject()
{
	return propertyObject_.get();
}

void RenderObject::OnPropertyChanged(const SPtr<PropertyObject>& obj, const std::string& name)
{

}

void RenderObject::OnPropertyChangedInternal(const SPtr<PropertyObject>& obj, const std::string& name)
{
	OnPropertyChanged(obj, name);
}
