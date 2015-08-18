#pragma once
#include "Render/RenderRectangle.h"
#include "Render/RenderObjectD2D.h"


class RenderRectangleD2D : public RenderObjectD2D<RenderRectangle>
{
public:
	RenderRectangleD2D();
	~RenderRectangleD2D();

	virtual CComPtr<ID2D1Geometry> GetPath() override;

	virtual base::Rect GetLocalBounds() override;
protected:	

	CComPtr<ID2D1Geometry> path_;
	
};


