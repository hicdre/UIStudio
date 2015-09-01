#pragma once
#include "Base/object.h"
#include "Base/Geom/size.h"
#include "Base/color.h"
#include "Render/RenderBrush.h"
#include "Render/RenderPen.h"
#include "Render/RenderPath.h"
#include "Render/RenderFont.h"
#include "Render/RenderPathBuilder.h"

class RenderContext;
class RenderWindow;

class RenderEngine
{
public:
	enum Type {
		D2D,
		GDI
	};
	static void InitEngine(Type type);
	static void UninitEngine();
	static RenderEngine* Get();	

	static SPtr<RenderContext>
		NewRenderContext(const SPtr<RenderWindow>& window);
	
	static SPtr<RenderBrush>
		NewRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color);

	static SPtr<RenderPen>
		NewRenderPen(const SPtr<RenderBrush>& brush, float width);

	static SPtr<RenderPath>
		NewRenderRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect);

	static SPtr<RenderPath>
		NewRenderRoundRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect, float rx, float ry);

	static SPtr<RenderPathBuilder>
		NewRenderPathBuilder(const SPtr<RenderContext>& context);

	static SPtr<RenderFont>
		NewRenderFont(const std::wstring& family, AttributeFontWeight weight, AttributeFontStyle style, float size);
public:
	virtual SPtr<RenderContext>
		CreateRenderContext(const SPtr<RenderWindow>& window) = 0;

	virtual SPtr<RenderBrush>
		CreateRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color) = 0;

	virtual SPtr<RenderPen>
		CreateRenderPen(const SPtr<RenderBrush>& brush, float width) = 0;

	virtual SPtr<RenderPath>
		CreateRenderRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect) = 0;

	virtual SPtr<RenderPath>
		CreateRenderRoundRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect, float rx, float ry) = 0;

	virtual SPtr<RenderPathBuilder>
		CreateRenderPathBuilder(const SPtr<RenderContext>& context) = 0;

	virtual SPtr<RenderFont>
		CreateRenderFont(const std::wstring& family, AttributeFontWeight weight, AttributeFontStyle style, float size) = 0;
};