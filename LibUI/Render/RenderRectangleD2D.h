#pragma once
#include "Render/RenderRectangle.h"
#include "Render/RenderObjectD2D.h"


class RenderRectangleD2D : public RenderObjectD2D<RenderRectangle>
{
public:
	RenderRectangleD2D();
	~RenderRectangleD2D();

	virtual CComPtr<ID2D1Geometry> GetPath() override;


protected:
	virtual void OnSizeChanged() override;
	virtual void OnRadiusChanged() override;

	CComPtr<ID2D1Geometry> path_;

	

	bool isPathDirty_;
};


