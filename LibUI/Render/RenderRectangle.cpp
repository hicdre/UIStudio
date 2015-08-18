#include "stdafx.h"
#include "RenderRectangle.h"

RenderRectangle::RenderRectangle()
	: cornerRadiusX_(0)
	, cornerRadiusY_(0)
{

}

RenderRectangle::~RenderRectangle()
{

}

void RenderRectangle::SetWidth(float width)
{
	if (rectangleSize_.width() == width)
		return;
	rectangleSize_.set_width(width);
	SetRenderObjectDirty(true);
}

void RenderRectangle::SetHeight(float height)
{
	if (rectangleSize_.height() == height)
		return;
	rectangleSize_.set_height(height);
	SetRenderObjectDirty(true);
}

void RenderRectangle::SetRadiusX(float rx)
{
	if (cornerRadiusX_ == rx)
		return;
	cornerRadiusX_ = rx;
	SetRenderObjectDirty(true);
}

void RenderRectangle::SetRadiusY(float ry)
{
	if (cornerRadiusY_ == ry)
		return;
	cornerRadiusY_ = ry;
	SetRenderObjectDirty(true);
}





