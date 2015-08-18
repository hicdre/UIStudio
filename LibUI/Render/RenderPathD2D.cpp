#include "stdafx.h"
#include "RenderPathD2D.h"

RenderPathD2D::RenderPathD2D(const CComPtr<ID2D1Geometry>& g)
	: d2dGeometry_(g)
{

}

RenderPathD2D::RenderPathD2D(const CComPtr<ID2D1RectangleGeometry >& g)
	: d2dGeometry_(g)
{

}

RenderPathD2D::RenderPathD2D(const CComPtr<ID2D1RoundedRectangleGeometry >& g)
	: d2dGeometry_(g)
{

}

RenderPathD2D::RenderPathD2D(const CComPtr<ID2D1PathGeometry >& g)
	: d2dGeometry_(g)
{

}

RenderPathD2D::~RenderPathD2D()
{

}

base::Rect RenderPathD2D::GetBounds()
{
	D2D1_RECT_F bounds;
	d2dGeometry_->GetBounds(D2D1::Matrix3x2F::Identity(), &bounds);
	return base::Rect(bounds.left, bounds.top,
		bounds.right - bounds.left, bounds.bottom - bounds.top);
}
