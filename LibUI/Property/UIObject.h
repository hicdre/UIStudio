#pragma once
#include "Property/PropertyObject.h"
#include "Delegate/Delegate.h"

class RenderObject;
class LayoutObject;
class LayoutContainer;
class UIObject : public PropertyObject
{
public:
	UIObject();
	~UIObject();

	Event<void(const SPtr<UIObject>&)> EventVisibleChanged;
	bool GetPropertyVisible() const;
	void SetPropertyVisible(bool show);	

	Event<void(const SPtr<UIObject>&)> EventLayoutChanged;	
	const base::Size& GetPropertySize() const;
	void SetPropertySize(int w, int h);
	virtual SPtr<LayoutObject> GetLayoutObject() = 0;	

	void SetLayoutContainer(const SPtr<LayoutContainer>& obj);
	const SPtr<LayoutContainer>& GetLayoutContainer() const;	

	
	virtual SPtr<RenderObject> GetRenderObject() = 0;
protected:
	SPtr<LayoutContainer> layoutContainer_;
	bool propertyVisible_;
	base::Size propertySize_;
};