#pragma once
#include "Base/object.h"

class PropertyObject;
class RenderObject : public Object
{
public:
	RenderObject();
	~RenderObject();

	virtual void Render();

	void Attatch(const SPtr<PropertyObject>& object);
	void Detach();

	SPtr<PropertyObject> GetPropertyObject();
protected:
	
	WPtr<PropertyObject> propertyObject_;
};