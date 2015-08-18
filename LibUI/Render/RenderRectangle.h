#pragma once
#include "Render/RenderObject.h"
#include "Base/color.h"

class RenderRectangle : public RenderObject
{
public:
	RenderRectangle();
	~RenderRectangle();

	float GetWidth() const { return rectangleSize_.width(); }
	float GetHeight() const { return rectangleSize_.height(); }
	float GetRadiusX() const { return cornerRadiusX_; }
	float GetRadiusY() const { return cornerRadiusY_; }
	
	void SetWidth(float width);
	void SetHeight(float height);
	void SetRadiusX(float rx);
	void SetRadiusY(float ry);
protected:	
	float cornerRadiusX_;
	float cornerRadiusY_;
	base::SizeF rectangleSize_;
};