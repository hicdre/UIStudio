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
}

void RenderObject::Detach()
{
	propertyObject_.reset();
}

SPtr<PropertyObject> RenderObject::GetPropertyObject()
{
	return propertyObject_.get();
}
