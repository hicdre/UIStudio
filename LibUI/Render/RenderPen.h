#pragma once
#include "Base/object.h"
#include "Model/AttributeConst.h"



class RenderPen : public Object
{
public:
	RenderPen();
	~RenderPen();

	virtual void SetLineJoin(AttributeStrokeLineJoin v) = 0;
	virtual void SetLineCap(AttributeStrokeLineCap v) = 0;
	virtual void SetLineMiterLimit(float v) = 0;
};