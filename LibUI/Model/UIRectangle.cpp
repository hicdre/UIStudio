#include "stdafx.h"
#include "UIRectangle.h"
#include "Render/RenderEngine.h"

UIRectangle::UIRectangle()
	: x_(AttributeLength::Pixel(0))
	, y_(AttributeLength::Pixel(0))
	, width_(AttributeLength::Pixel(0))
	, height_(AttributeLength::Pixel(0))
	, rx_(AttributeLength::Pixel(0))
	, ry_(AttributeLength::Pixel(0))
{

}

UIRectangle::~UIRectangle()
{

}

SPtr<AttributeLength> UIRectangle::GetX() const
{
	return x_;
}

void UIRectangle::SetX(const SPtr<AttributeLength>& v)
{
	if (x_->IsEqual(v.get()))
		return;
	x_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("x", x_));
}

SPtr<AttributeLength> UIRectangle::GetY() const
{
	return y_;
}

void UIRectangle::SetY(const SPtr<AttributeLength>& v)
{
	if (y_->IsEqual(v.get()))
		return;
	y_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("y", y_));
}

SPtr<AttributeLength> UIRectangle::GetWidth() const
{
	return width_;
}

void UIRectangle::SetWidth(const SPtr<AttributeLength>& v)
{
	if (width_->IsEqual(v.get()))
		return;
	width_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("width", width_));
}

SPtr<AttributeLength> UIRectangle::GetHeight() const
{
	return height_;
}

void UIRectangle::SetHeight(const SPtr<AttributeLength>& v)
{
	if (height_->IsEqual(v.get()))
		return;
	height_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("height", height_));
}

SPtr<AttributeLength> UIRectangle::GetRadiusX() const
{
	return rx_;
}

void UIRectangle::SetRadiusX(const SPtr<AttributeLength>& v)
{
	if (rx_->IsEqual(v.get()))
		return;
	rx_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("rx", rx_));
}

SPtr<AttributeLength> UIRectangle::GetRadiusY() const
{
	return ry_;
}

void UIRectangle::SetRadiusY(const SPtr<AttributeLength>& v)
{
	if (ry_->IsEqual(v.get()))
		return;
	ry_ = v;
	SetPathDirty(true);
	OnAttributeChanged(new AttributeEventArgs("ry", ry_));
}

SPtr<RenderPath> UIRectangle::GetPath(const SPtr<RenderContext>& context)
{
	if (!renderPath_ || IsPathDirty())
	{
		float rx, ry;
		base::Rect rect = CalcRect(rx, ry);
		if (rx == 0.0f && ry == 0.0f)
		{
			renderPath_ = RenderEngine::NewRenderRectanglePath(context, rect);
		}
		else
		{
			renderPath_ = RenderEngine::NewRenderRoundRectanglePath(context, rect, rx, ry);
		}
		SetPathDirty(false);
	}
	return renderPath_;
}

base::Rect UIRectangle::GetBounds()
{
	return GetPath(NULL)->GetBounds();
}

base::Rect UIRectangle::CalcRect(float& rx, float& ry)
{
	float x, y, w, h;
	SPtr<UIVisualObject> obj = GetVisualParent();
	base::Rect bounds(obj->GetLocalBounds());
	x = AttributeLength::CalcFromBounds(x_, bounds.width());
	y = AttributeLength::CalcFromBounds(y_, bounds.height());
	w = AttributeLength::CalcFromBounds(width_, bounds.width());
	h = AttributeLength::CalcFromBounds(height_, bounds.height());
	rx = AttributeLength::CalcFromBounds(rx_, bounds.width());
	ry = AttributeLength::CalcFromBounds(ry_, bounds.height());
	return base::Rect(x, y, w, h);
}

