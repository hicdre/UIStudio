#pragma once
#include "Render/RenderObject.h"
#include "Base/color.h"

class RenderRectangle : public RenderObject
{
public:
	RenderRectangle();
	~RenderRectangle();
	
	void SetFilledColor(base::Color color);

protected:
	base::Color color_;
};