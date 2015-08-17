#include "stdafx.h"
#include "UIObject.h"
#include "Layout/LayoutObject.h"
#include "Layout/LayoutContainer.h"
#include "Render/RenderObject.h"

UIObject::UIObject()
	: propertyVisible_(true)	
{

}

UIObject::~UIObject()
{

}

bool UIObject::GetPropertyVisible() const
{
	return propertyVisible_;
}

void UIObject::SetPropertyVisible(bool show)
{
	if (propertyVisible_ == show)
		return;
	propertyVisible_ = show;
	EventPropertyVisibleChanged.Execute(GetSelf<UIObject>());
}

const base::Size& UIObject::GetPropertySize() const
{
	return propertySize_;
}

void UIObject::SetPropertySize(int w, int h)
{
	if (propertySize_.width() == w && propertySize_.height() == h)
		return;
	propertySize_.SetSize(w, h);
	EventPropertySizeChanged.Execute(GetSelf<UIObject>());
}

void UIObject::SetLayoutContainer(const SPtr<LayoutContainer>& obj)
{
	layoutContainer_->Detach();
	layoutContainer_ = obj;
	layoutContainer_->Attatch(GetSelf<UIObject>());
}

const SPtr<LayoutContainer>& UIObject::GetLayoutContainer() const
{
	return layoutContainer_;
}

void UIObject::OnLayoutSizeChanged()
{
	GetRenderObject()->SetSize(GetLayoutObject()->size());
}

