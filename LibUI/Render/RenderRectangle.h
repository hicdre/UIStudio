#pragma once
#include "Render/RenderObject.h"
#include "Base/color.h"

class RenderRectangle : public RenderObject
{
public:
	RenderRectangle();
	~RenderRectangle();

	float GetRadiusX() const { return cornerRadiusX_; }
	float GetRadiusY() const { return cornerRadiusY_; }
	
	void SetRadiusX(float rx);
	void SetRadiusY(float ry);

protected:
	virtual void OnRadiusChanged();
	int cornerRadiusX_;
	int cornerRadiusY_;
};