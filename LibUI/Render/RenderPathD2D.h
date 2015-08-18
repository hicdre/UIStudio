#pragma once
#include "Render/RenderPath.h"
#include "Render/RenderD2DUtils.h"

class RenderPathD2D : public RenderPath
{
public:
	RenderPathD2D(const CComPtr<ID2D1Geometry>& g);
	~RenderPathD2D();

	CComPtr<ID2D1Geometry> GetRealPath() const { return d2dGeometry_; }
private:
	CComPtr<ID2D1Geometry> d2dGeometry_;
};