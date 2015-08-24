#pragma once
#include "Base/object.h"
#include "Base/Geom/size.h"
#include "Base/Geom/point.h"
#include <string>

class RenderContext;
class RenderPath;
class RenderFont : public Object
{
public:
	RenderFont();
	~RenderFont();

	virtual float GetSize() = 0;

	virtual void AddStringToPath(const SPtr<RenderContext>& renderer, const SPtr<RenderPath>& path, const std::wstring& text, const base::PointF& location) = 0;
	virtual float GetAscent(const SPtr<RenderContext>& renderer) = 0;
	//IList<RectangleF> MeasureCharacters(ISvgRenderer renderer, string text);
	virtual base::SizeF MeasureString(const SPtr<RenderContext>& renderer, const std::wstring& text) = 0;
};