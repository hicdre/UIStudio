#include "stdafx.h"
#include "RenderBrushD2D.h"

RenderBrushD2D::RenderBrushD2D(const CComPtr<ID2D1Brush>& b)
	: realBrush_(b)
{

}

RenderBrushD2D::RenderBrushD2D(const CComPtr<ID2D1SolidColorBrush>& b)
	: realBrush_(b)
{

}

RenderBrushD2D::~RenderBrushD2D()
{

}

CComPtr<ID2D1Brush> RenderBrushD2D::Get(const SPtr<RenderBrush>& b)
{
	SPtr<RenderBrushD2D> d2d = b;
	if (!d2d)
		return NULL;
	return d2d->GetRealBrush();
}
