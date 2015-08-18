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
