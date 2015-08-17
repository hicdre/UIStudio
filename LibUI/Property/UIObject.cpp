#include "stdafx.h"
#include "UIObject.h"
#include "UIObjectCollection.h"
#include "Layout/LayoutObject.h"
#include "Layout/LayoutContainer.h"
#include "Render/RenderObject.h"

UIObject::UIObject()
	: propertyWidth_(new PropertyLengthValue)
	, propertyHeight_(new PropertyLengthValue)
	, propertyX_(new PropertyLengthValue)
	, propertyY_(new PropertyLengthValue)
	, propertyVisible_(true)
	, isRenderObjectNeedsUpdate_(true)
	, isLayoutObjectNeedsUpdate_(true)
	//, attributes_(new PropertyObject)
{
	
}

UIObject::~UIObject()
{

}


SPtr<PropertyLengthValue> UIObject::GetWidth()
{
	return propertyWidth_;
}

void UIObject::SetWidthAuto()
{
	if (PropertyLengthSetAuto(propertyWidth_.get()))
		isLayoutObjectNeedsUpdate_ = true;
}

void UIObject::SetWidthPixel(uint32_t pixel)
{
	if (PropertyLengthSetPixel(propertyWidth_.get(), pixel))
		isLayoutObjectNeedsUpdate_ = true;
}

void UIObject::SetWidthPercent(float percent)
{
	if (PropertyLengthSetPercent(propertyWidth_.get(), percent))
		isLayoutObjectNeedsUpdate_ = true;
}

SPtr<PropertyLengthValue> UIObject::GetHeight()
{
	return propertyHeight_;
}

void UIObject::SetHeightAuto()
{
	if (PropertyLengthSetAuto(propertyHeight_.get()))
		isLayoutObjectNeedsUpdate_ = true;
}

void UIObject::SetHeightPixel(uint32_t pixel)
{
	if (PropertyLengthSetPixel(propertyHeight_.get(), pixel))
		isLayoutObjectNeedsUpdate_ = true;
}

void UIObject::SetHeightPercent(float percent)
{
	if (PropertyLengthSetPercent(propertyHeight_.get(), percent))
		isLayoutObjectNeedsUpdate_ = true;
}

bool UIObject::PropertyLengthSetAuto(PropertyLengthValue* val)
{
	if (val->IsEqualAuto())
		return false;
	val->SetAuto();
	return true;
}

bool UIObject::PropertyLengthSetPixel(PropertyLengthValue* val, uint32_t pixel)
{
	if (val->IsEqualPixel(pixel))
		return false;
	val->SetPixel(pixel);
	return true;
}

bool UIObject::PropertyLengthSetPercent(PropertyLengthValue* val, float percent)
{
	if (val->IsEqualPercent(percent))
		return false;
	val->SetPercent(percent);
	return true;
}

bool UIObject::IsVisible() const
{
	return propertyVisible_;
}

void UIObject::SetVisible(bool visible)
{
	if (propertyVisible_ == visible)
		return;
	propertyVisible_ = visible;
	
}

void UIObject::SetLayoutContainerType(LayoutContainerType type)
{
	if (layoutContainerType_ == type)
		return;
	layoutContainerType_ = type;
	isLayoutContainerChanged_ = true;

	SPtr<UIObjectCollection> collection = GetChildren();
	for (auto obj : *collection.get())
	{
		obj->OnParentLayoutContainerTypeChanged(layoutContainerType_);
	}
}

LayoutContainerType UIObject::GetLayoutContainerType()
{
	return layoutContainerType_;
}


void UIObject::OnParentLayoutContainerTypeChanged(LayoutContainerType type)
{
	//根据自身的属性和type共同判断
	//if (type == RelativeLayout)
	isLayoutObjectNeedsUpdate_ = false;
}

SPtr<UIObjectCollection> UIObject::GetChildren()
{
	if (!children_)
	{
		children_.reset(new UIObjectCollection(GetSelf<UIObject>()));
	}
	return children_;
}

void UIObject::OnChildRemoved(const SPtr<UIObject>& obj)
{
	GetLayoutContainer()->SetNeedsLayout();
}

SPtr<PropertyLengthValue> UIObject::GetX()
{
	return propertyX_;
}

void UIObject::SetXPixel(uint32 pixel)
{
	PropertyLengthSetPixel(propertyX_.get(), pixel);
}

SPtr<PropertyLengthValue> UIObject::GetY()
{
	return propertyY_;
}

void UIObject::SetYPixel(uint32 pixel)
{
	PropertyLengthSetPixel(propertyY_.get(), pixel);
}

void UIObject::OnLayoutObjectSizeChanged()
{

}

void UIObject::SetRenderObjectNeedsUpdate()
{
	isRenderObjectNeedsUpdate_ = true;
}

bool UIObject::IsRenderObjectNeedsUpdate() const
{
	return isRenderObjectNeedsUpdate_;
}

