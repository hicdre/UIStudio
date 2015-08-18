#include "stdafx.h"
#include "UIObject.h"
#include "UIObjectCollection.h"
#include "Layout/LayoutObject.h"
#include "Layout/LayoutContainer.h"
#include "Render/RenderObject.h"
#include "AttributePaint.h"

UIObject::UIObject()
// 	: isRenderObjectNeedsUpdate_(true)
// 	, isLayoutObjectNeedsUpdate_(true)
	//, attributes_(new PropertyObject)
{
	
}

UIObject::~UIObject()
{

}

SPtr<UIObjectCollection> UIObject::GetChildren()
{
	if (!children_)
	{
		children_.reset(new UIObjectCollection(GetSelf<UIObject>()));
	}
	return children_;
}

bool UIObject::HasChildren()
{
	return !GetChildren()->IsEmpty();
}

SPtr<UIObject> UIObject::GetParent()
{
	return parent_.get();
}

SPtr<AttributeCollection> UIObject::GetAttributes()
{
	if (!attributes_)
	{
		attributes_.reset(new AttributeCollection(GetSelf<UIObject>()));
		attributes_->EventAttributechanged.AddW(GetWeak<UIObject>(), &UIObject::OnAttributesAttributeChanged);
	}
	return attributes_;
}

void UIObject::Render(const SPtr<RenderContext>& context)
{
	RenderChildren(context);
}

void UIObject::SetPathDirty(bool dirty)
{
	isPathDirty_ = dirty;
}

SPtr<AttributePaint> UIObject::GetColor()
{
	return !GetAttributes()->HasAttribute("color")
		? AttributeColorPaint::NotSet()
		: GetAttributes()->GetAttributePaint("color");
}

void UIObject::SetColor(const SPtr<AttributePaint>& p)
{
	GetAttributes()->SetAttributePaint("color", p);
}

SPtr<AttributePaint> UIObject::GetFill()
{
	return !GetAttributes()->HasAttribute("fill")
		? AttributeColorPaint::NotSet()
		: GetAttributes()->GetAttributePaint("fill");
}

void UIObject::SetFill(const SPtr<AttributePaint>& v)
{
	GetAttributes()->SetAttributePaint("fill", v);
}

SPtr<AttributePaint> UIObject::GetStroke()
{
	return !GetAttributes()->HasAttribute("stroke")
		? AttributeColorPaint::NotSet()
		: GetAttributes()->GetAttributePaint("stroke");
}

void UIObject::SetStroke(const SPtr<AttributePaint>& v)
{
	GetAttributes()->SetAttributePaint("stroke", v);
}

float UIObject::GetFillOpacity()
{
	return !GetAttributes()->HasAttribute("fill-opacity")
		? GetOpacity()
		: GetAttributes()->GetAttributeFloat("fill-opacity");
}

void UIObject::SetFillOpacity(float v)
{
	GetAttributes()->SetAttributeFloat("fill-opacity", FixOpacityValue(v));
}

float UIObject::GetStrokeWidth()
{
	return !GetAttributes()->HasAttribute("stroke-width")
		? 1.0f
		: GetAttributes()->GetAttributeFloat("stroke-width");
}

void UIObject::SetStrokeWidth(float v)
{
	GetAttributes()->SetAttributeFloat("stroke-width", v);
}

float UIObject::GetStrokeOpacity()
{
	return !GetAttributes()->HasAttribute("stroke-opacity")
		? GetOpacity()
		: GetAttributes()->GetAttributeFloat("stroke-opacity");
}

void UIObject::SetStrokeOpacity(float v)
{
	GetAttributes()->SetAttributeFloat("stroke-opacity", FixOpacityValue(v));
}

SPtr<AttributePaint> UIObject::GetStopColor()
{
	return !GetAttributes()->HasAttribute("stop-color")
		? AttributeColorPaint::NotSet()
		: GetAttributes()->GetAttributePaint("stop-color");
}

void UIObject::SetStopColor(const SPtr<AttributePaint>& v)
{
	GetAttributes()->SetAttributePaint("stop-color", v);
}

float UIObject::GetOpacity()
{
	return !GetAttributes()->HasAttribute("opacity")
		? GetOpacity()
		: GetAttributes()->GetAttributeFloat("opacity");
}

void UIObject::SetOpacity(float v)
{
	GetAttributes()->SetAttributeFloat("opacity", FixOpacityValue(v));
}

std::wstring UIObject::GetFontFamily()
{
	return GetAttributes()->GetAttributeUTF16("font-family");
}

void UIObject::SetFontFamily(const std::wstring& v)
{
	GetAttributes()->SetAttributeString("font-family",v);
	SetPathDirty(true);
}

uint32 UIObject::GetFontSize()
{
	return GetAttributes()->HasAttribute("font-size")
		? GetAttributes()->GetAttributeUInt("font-size")
		: GetOpacity();
}

void UIObject::SetFontSize(uint32 v)
{
	GetAttributes()->SetAttributeUInt("font-size", v);
	SetPathDirty(true);
}

void UIObject::RenderChildren(const SPtr<RenderContext>& context)
{
	for (auto obj : *children_.get())
	{
		obj->Render(context);
	}
}

// SPtr<AttributeLength> UIObject::GetX()
// {
// 	return GetAttributes()->GetAttributeLength("x");
// }
// 
// SPtr<AttributeLength> UIObject::GetY()
// {
// 	return GetAttributes()->GetAttributeLength("y");
// }
// 
// SPtr<AttributeLength> UIObject::GetWidth()
// {
// 	return GetAttributes()->GetAttributeLength("width");
// }
// 
// SPtr<AttributeLength> UIObject::GetHeight()
// {
// 	return GetAttributes()->GetAttributeLength("height");
// }
// 
// void UIObject::SetX(const SPtr<AttributeLength>& v)
// {
// 	GetAttributes()->SetAttributeLength("x", v);
// }
// 
// void UIObject::SetY(const SPtr<AttributeLength>& v)
// {
// 	GetAttributes()->SetAttributeLength("y", v);
// }
// 
// void UIObject::SetWidth(const SPtr<AttributeLength>& v)
// {
// 	GetAttributes()->SetAttributeLength("width", v);
// }
// 
// void UIObject::SetHeight(const SPtr<AttributeLength>& v)
// {
// 	GetAttributes()->SetAttributeLength("height", v);
// }
// 
// bool UIObject::IsVisible()
// {
// 	return GetAttributes()->GetAttributeBool("visible");
// }
// 
// void UIObject::SetVisible(bool visible)
// {
// 	GetAttributes()->SetAttributeBool("visible", visible);
// }
// 
// void UIObject::SetLayoutContainerType(LayoutContainerType type)
// {
// 	GetAttributes()->SetAttributeInt("layout", type);
// }
// 
// LayoutContainerType UIObject::GetLayoutContainerType()
// {
// 	return (LayoutContainerType)GetAttributes()->GetAttributeInt("layout");
// }
// 
// void UIObject::SetRenderObjectNeedsUpdate(bool v)
// {
// 	isRenderObjectNeedsUpdate_ = v;
// }
// 
// bool UIObject::IsRenderObjectNeedsUpdate() const
// {
// 	return isRenderObjectNeedsUpdate_;
// }
// 
// void UIObject::OnParentLayoutContainerTypeChanged(LayoutContainerType type)
// {
// 	//根据自身的属性和type共同判断
// 	//if (type == RelativeLayout)
// 	isLayoutObjectNeedsUpdate_ = false;
// }
// 
// void UIObject::OnChildRemoved(const SPtr<UIObject>& obj)
// {
// 	GetLayoutContainer()->SetNeedsLayout();
// }
// 
// void UIObject::OnLayoutObjectSizeChanged()
// {
// 
// }

void UIObject::OnAttributesAttributeChanged(const SPtr<UIObject>& owner, const SPtr<AttributeEventArgs>& args)
{
	OnAttributeChanged(args);
}

void UIObject::OnAttributeChanged(const SPtr<AttributeEventArgs>& args)
{
	EventAttributechanged.Execute(GetSelf<UIObject>(), args);
}

float UIObject::FixOpacityValue(float v)
{
	if (v < 0.0f)
		return 0.0f;
	if (v > 1.0f)
		return 1.0f;
	return v;
}

