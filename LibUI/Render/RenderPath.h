#pragma once
#include "Base/object.h"
#include "Base/Geom/rect.h"

class RenderPath : public Object
{
public:
	RenderPath();
	~RenderPath();

	virtual base::Rect GetBounds() = 0;
};