#pragma once
#include "Base/object.h"
#include "Base/Geom/rect.h"
#include "Base/Geom/matrix.h"
#include "Base/color.h"

class RenderBrush;
class RenderPath;
class RenderContext : public Object
{
public:
	virtual void Transform(const base::Matrix& m) = 0;

	virtual void FillPath(const SPtr<RenderBrush>& brush, const SPtr<RenderPath>& path) = 0;
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