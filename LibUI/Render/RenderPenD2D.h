#pragma once
#include "Render/RenderPen.h"
#include "Render/RenderD2DUtils.h"

class RenderPenD2D : public RenderPen
{
public:
	RenderPenD2D(const CComPtr<ID2D1Brush>& b, float strokeWidth);
	~RenderPenD2D();

	virtual void SetLineJoin(AttributeStrokeLineJoin v) override;
	virtual void SetLineCap(AttributeStrokeLineCap v) override;
	virtual void SetLineMiterLimit(float v) override;

	CComPtr<ID2D1Brush> GetRealBrush() const { return realBrush_; }
	float GetStrokeWidth() const { return strokeWidth_; }

	D2D1_STROKE_STYLE_PROPERTIES GetStrokeStyle() const;
private:
	CComPtr<ID2D1Brush> realBrush_;
	float strokeWidth_;
	
	AttributeStrokeLineJoin lineJoin_;
	AttributeStrokeLineCap lineCap_;
	float milterLimit_;
};