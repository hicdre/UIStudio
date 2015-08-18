#include "stdafx.h"
#include "RenderRectangleD2D.h"
#include "RenderEngineD2D.h"

RenderRectangleD2D::RenderRectangleD2D()	
{

}

RenderRectangleD2D::~RenderRectangleD2D()
{

}

CComPtr<ID2D1Geometry> RenderRectangleD2D::GetPath()
{
	if (!path_ || IsRenderObjectDirty())
	{
		CComPtr<ID2D1Factory> factory = RenderD2DEngine::GetD2DFactory();
		base::Rect rect(GetWidth(), GetHeight());
		if (cornerRadiusX_ == 0 && cornerRadiusY_ == 0)
		{
			factory->CreateRectangleGeometry(D2DRect(rect), (ID2D1RectangleGeometry**)&path_);
		}			
		else
		{
			factory->CreateRoundedRectangleGeometry(D2DRoundRect(rect, cornerRadiusX_, cornerRadiusY_), (ID2D1RoundedRectangleGeometry**)&path_);
		}
		SetRenderObjectDirty(false);
	}
	return path_;
}

base::Rect RenderRectangleD2D::GetLocalBounds()
{
	D2D1_RECT_F bounds;
	GetPath()->GetBounds(D2D1::Matrix3x2F::Identity(), &bounds);
	return base::Rect(0, 0, bounds.right - bounds.left, bounds.bottom - bounds.top);
}


