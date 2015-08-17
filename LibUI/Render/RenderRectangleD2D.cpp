#include "stdafx.h"
#include "RenderRectangleD2D.h"
#include "RenderEngineD2D.h"

RenderRectangleD2D::RenderRectangleD2D()
	: isPathDirty_(true)
{

}

RenderRectangleD2D::~RenderRectangleD2D()
{

}

CComPtr<ID2D1Geometry> RenderRectangleD2D::GetPath()
{
	if (!path_ || isPathDirty_)
	{
		CComPtr<ID2D1Factory> factory = RenderD2DEngine::GetD2DFactory();
		if (cornerRadiusX_ == 0 && cornerRadiusY_ == 0)
		{
			factory->CreateRectangleGeometry(D2DRect(GetLocalBounds()), (ID2D1RectangleGeometry**)&path_);			
		}			
		else
		{
			factory->CreateRoundedRectangleGeometry(D2DRoundRect(GetLocalBounds(), cornerRadiusX_, cornerRadiusY_), (ID2D1RoundedRectangleGeometry**)&path_);
		}
		isPathDirty_ = false;
	}
	return path_;
}

void RenderRectangleD2D::OnSizeChanged()
{
	isPathDirty_ = true;
}

void RenderRectangleD2D::OnRadiusChanged()
{
	isPathDirty_ = true;
}


