#include "stdafx.h"
#include "RenderPenD2D.h"

RenderPenD2D::RenderPenD2D(const CComPtr<ID2D1Brush>& b, float strokeWidth)
	: realBrush_(b)
	, strokeWidth_(strokeWidth)
	, lineJoin_(StrokeLineJoinMilter)
	, lineCap_(StrokeLineCapFlat)
	, milterLimit_(1.0f)
{

}

RenderPenD2D::~RenderPenD2D()
{

}

void RenderPenD2D::SetLineJoin(AttributeStrokeLineJoin v)
{
	lineJoin_ = v;
}

void RenderPenD2D::SetLineCap(AttributeStrokeLineCap v)
{
	lineCap_ = v;
}

void RenderPenD2D::SetLineMiterLimit(float v)
{
	milterLimit_ = v;
}

D2D1_STROKE_STYLE_PROPERTIES RenderPenD2D::GetStrokeStyle() const
{
	return D2D1::StrokeStyleProperties(
		D2DLineCap(lineCap_),
		D2DLineCap(lineCap_),
		D2DLineCap(lineCap_),
		D2DLineJoin(lineJoin_),
		milterLimit_
	);
}
