#include "stdafx.h"
#include "UIObject.h"
#include "UIObjectCollection.h"
#include "Layout/LayoutObject.h"
#include "Layout/LayoutContainer.h"
#include "Render/RenderObject.h"

UIObject::UIObject()
	: isRenderObjectNeedsUpdate_(true)
	, isLayoutObjectNeedsUpdate_(true)
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

SPtr<AttributeCollection> UIObject::GetAttributes()
{
	if (!attributes_)
	{
		attributes_.reset(new AttributeCollection(GetSelf<UIObject>()));
		attributes_->EventAttributechanged.AddW(GetWeak<UIObject>(), &UIObject::OnAttributesAttributeChanged);
	}
	return attributes_;
}

SPtr<AttributeLength> UIObject::GetX()
{
	return GetAttributes()->GetAttributeLength("x");
}

SPtr<AttributeLength> UIObject::GetY()
{
	return GetAttributes()->GetAttributeLength("y");
}

SPtr<AttributeLength> UIObject::GetWidth()
{
	return GetAttributes()->GetAttributeLength("width");
}

SPtr<AttributeLength> UIObject::GetHeight()
{
	return GetAttributes()->GetAttributeLength("height");
}

void UIObject::SetX(const SPtr<AttributeLength>& v)
{
	GetAttributes()->SetAttributeLength("x", v);
}

void UIObject::SetY(const SPtr<AttributeLength>& v)
{
	GetAttributes()->SetAttributeLength("y", v);
}

void UIObject::SetWidth(const SPtr<AttributeLength>& v)
{
	GetAttributes()->SetAttributeLength("width", v);
}

void UIObject::SetHeight(const SPtr<AttributeLength>& v)
{
	GetAttributes()->SetAttributeLength("height", v);
}

bool UIObject::IsVisible()
{
	return GetAttributes()->GetAttributeBool("visible");
}

void UIObject::SetVisible(bool visible)
{
	GetAttributes()->SetAttributeBool("visible", visible);
}

void UIObject::SetLayoutContainerType(LayoutContainerType type)
{
	GetAttributes()->SetAttributeInt("layout", type);
}

LayoutContainerType UIObject::GetLayoutContainerType()
{
	return (LayoutContainerType)GetAttributes()->GetAttributeInt("layout");
}

void UIObject::SetRenderObjectNeedsUpdate(bool v)
{
	isRenderObjectNeedsUpdate_ = v;
}

bool UIObject::IsRenderObjectNeedsUpdate() const
{
	return isRenderObjectNeedsUpdate_;
}

void UIObject::OnParentLayoutContainerTypeChanged(LayoutContainerType type)
{
	//根据自身的属性和type共同判断
	//if (type == RelativeLayout)
	isLayoutObjectNeedsUpdate_ = false;
}

void UIObject::OnChildRemoved(const SPtr<UIObject>& obj)
{
	GetLayoutContainer()->SetNeedsLayout();
}

void UIObject::OnLayoutObjectSizeChanged()
{

}

void UIObject::OnAttributesAttributeChanged(const SPtr<UIObject>& owner, const SPtr<AttributeEventArgs>& args)
{
	OnAttributeChanged(args);
}

void UIObject::OnAttributeChanged(const SPtr<AttributeEventArgs>& args)
{
	EventAttributechanged.Execute(GetSelf<UIObject>(), args);
}

