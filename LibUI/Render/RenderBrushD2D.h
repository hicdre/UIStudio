#pragma once
#include "Render/RenderBrush.h"
#include "Render/RenderD2DUtils.h"

class RenderBrushD2D : public RenderBrush
{
public:
	RenderBrushD2D(const CComPtr<ID2D1Brush>& b);
	RenderBrushD2D(const CComPtr<ID2D1SolidColorBrush>& b);
	~RenderBrushD2D();

	CComPtr<ID2D1Brush> GetRealBrush() const { return realBrush_; }

	static CComPtr<ID2D1Brush> Get(const SPtr<RenderBrush>& b);
private:
	CComPtr<ID2D1Brush> realBrush_;
};