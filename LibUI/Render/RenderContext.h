#pragma once
#include "Base/object.h"
#include "Base/Geom/rect.h"
#include "Base/Geom/matrix.h"
#include "Base/color.h"

class RenderContext : public Object
{
public:
	virtual void Transform(const base::Matrix& m) = 0;
};

class ScopedRenderTransform
{
public:
	ScopedRenderTransform(const SPtr<RenderContext>& context, const base::Matrix& m);
	~ScopedRenderTransform();
private:
	SPtr<RenderContext> context_;
	base::Matrix m_;
};