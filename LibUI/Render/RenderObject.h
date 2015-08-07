#pragma once
#include "Base/object.h"
#include <string>

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
	virtual void OnPropertyChanged(const SPtr<PropertyObject>& obj, const std::string& name);
private:
	void OnPropertyChangedInternal(const SPtr<PropertyObject>& obj, const std::string& name);

protected:
	WPtr<PropertyObject> propertyObject_;
};