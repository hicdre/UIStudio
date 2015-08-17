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

void RenderRectangle::SetRadiusX(float rx)
{
	if (cornerRadiusX_ == rx)
		return;
	cornerRadiusX_ = rx;
	OnRadiusChanged();
}

void RenderRectangle::SetRadiusY(float ry)
{
	if (cornerRadiusY_ == ry)
		return;
	cornerRadiusY_ = ry;
	OnRadiusChanged();
}

void RenderRectangle::OnRadiusChanged()
{

}



