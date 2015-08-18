#pragma once
#include "Delegate/Delegate.h"
#include "Model/AttributeCollection.h"
#include "Layout/LayoutObject.h"

class RenderObject;
class LayoutObject;
class LayoutContainer;
class UIObjectCollection;
class UIObject : public Object
{
public:
	UIObject();
	~UIObject();

	SPtr<UIObjectCollection> GetChildren();

	SPtr<AttributeCollection> GetAttributes();		

	Event<void(const SPtr<UIObject>&, const SPtr<AttributeEventArgs>&)> EventAttributechanged;

	SPtr<AttributeLength> GetX();
	SPtr<AttributeLength> GetY();
	SPtr<AttributeLength> GetWidth();
	SPtr<AttributeLength> GetHeight();

	void SetX(const SPtr<AttributeLength>& v);
	void SetY(const SPtr<AttributeLength>& v);
	void SetWidth(const SPtr<AttributeLength>& v);
	void SetHeight(const SPtr<AttributeLength>& v);

	//visible
	bool IsVisible();
	void SetVisible(bool visible);

	//layout
	void SetLayoutContainerType(LayoutContainerType type);
	LayoutContainerType GetLayoutContainerType();
public:
	void SetRenderObjectNeedsUpdate(bool v);
	bool IsRenderObjectNeedsUpdate() const;

	virtual void OnParentLayoutContainerTypeChanged(LayoutContainerType type);

	virtual SPtr<LayoutObject> GetLayoutObject() = 0;	
	virtual SPtr<LayoutContainer> GetLayoutContainer() = 0;

	virtual SPtr<RenderObject> GetRenderObject() = 0;

	void OnChildRemoved(const SPtr<UIObject>& obj);

	virtual void OnLayoutObjectSizeChanged();
protected:	
	void OnAttributesAttributeChanged(const SPtr<UIObject>& owner, const SPtr<AttributeEventArgs>& args);
	void OnAttributeChanged(const SPtr<AttributeEventArgs>& args);
	
	SPtr<UIObjectCollection> children_;
	SPtr<AttributeCollection> attributes_;

	SPtr<AttributeLength> propertyX_;
	SPtr<AttributeLength> propertyY_;
	SPtr<AttributeLength> propertyWidth_;
	SPtr<AttributeLength> propertyHeight_;


	bool isRenderObjectNeedsUpdate_;
	bool isLayoutObjectNeedsUpdate_;
	bool isLayoutContainerChanged_;
	//SPtr<PropertyObject> attributes_;
};