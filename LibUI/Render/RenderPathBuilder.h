#pragma once
#include "Base/object.h"
#include "Base/Geom/point.h"
#include "Base/Geom/rect.h"
#include <string>

class RenderPath;
class RenderFont;
class RenderPathBuilder : public Object
{
public:
	RenderPathBuilder();
	~RenderPathBuilder();

	virtual SPtr<RenderPath> GetPath() = 0;

	virtual void BeginFigure() = 0;
	virtual void EndFigure() = 0;

	virtual void AddLine(const base::PointF& from, const base::PointF& to) = 0;

	virtual void AddEllipse(const base::Rect& rc) = 0;
};