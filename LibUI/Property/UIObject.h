#pragma once
#include "Property/PropertyObject.h"
#include "Delegate/Delegate.h"
#include "Property/PropertyLengthValue.h"
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

	//x
	SPtr<PropertyLengthValue> GetX();
	void SetXPixel(uint32 pixel);
	SPtr<PropertyLengthValue> GetY();
	void SetYPixel(uint32 pixel);
	//width
	SPtr<PropertyLengthValue> GetWidth();
	void SetWidthAuto();
	void SetWidthPixel(uint32 pixel);
	void SetWidthPercent(float percent);

	//height
	SPtr<PropertyLengthValue> GetHeight();
	void SetHeightAuto();
	void SetHeightPixel(uint32 pixel);
	void SetHeightPercent(float percent);

	//visbile
	bool IsVisible() const;
	void SetVisible(bool visible);

	//layout
	void SetLayoutContainerType(LayoutContainerType type);
	LayoutContainerType GetLayoutContainerType();	

	Event<void(const SPtr<UIObject>&, const std::string&)> EventPropertyChanged;

public:
	void SetRenderObjectNeedsUpdate();
	bool IsRenderObjectNeedsUpdate() const;

	virtual void OnParentLayoutContainerTypeChanged(LayoutContainerType type);

	virtual SPtr<LayoutObject> GetLayoutObject() = 0;	
	virtual SPtr<LayoutContainer> GetLayoutContainer() = 0;

	virtual SPtr<RenderObject> GetRenderObject() = 0;

	void OnChildRemoved(const SPtr<UIObject>& obj);

	virtual void OnLayoutObjectSizeChanged();
protected:	

	bool PropertyLengthSetAuto(PropertyLengthValue* val);//true:changed
	bool PropertyLengthSetPixel(PropertyLengthValue* val, uint32_t pixel);
	bool PropertyLengthSetPercent(PropertyLengthValue* val, float percent);
	SPtr<UIObjectCollection> children_;
	
	SPtr<PropertyLengthValue> propertyX_;
	SPtr<PropertyLengthValue> propertyY_;
	SPtr<PropertyLengthValue> propertyWidth_;
	SPtr<PropertyLengthValue> propertyHeight_;
	bool propertyVisible_;
	LayoutContainerType layoutContainerType_;

	bool isRenderObjectNeedsUpdate_;
	bool isLayoutObjectNeedsUpdate_;
	bool isLayoutContainerChanged_;
	//SPtr<PropertyObject> attributes_;
};