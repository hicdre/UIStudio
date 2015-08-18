#pragma once
#include "Base/object.h"
#include "Base/Geom/size.h"
#include "Base/color.h"
#include "Render/RenderBrush.h"
#include "Render/RenderPath.h"

class RenderContext;
class RenderWindow;
class RenderRectangle;

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

	static SPtr<RenderWindow> NewRenderWindow(const base::Size& sz);

	static SPtr<RenderContext>
		NewRenderContext(const SPtr<RenderWindow>& window);
	
	static SPtr<RenderBrush>
		NewRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color);

	static SPtr<RenderPath>
		NewRenderRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect);

	static SPtr<RenderPath>
		NewRenderRoundRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect, float rx, float ry);
public:
	virtual SPtr<RenderContext>
		CreateRenderContext(const SPtr<RenderWindow>& window) = 0;

	virtual SPtr<RenderBrush>
		CreateRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color) = 0;

	virtual SPtr<RenderPath>
		CreateRenderRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect) = 0;

	virtual SPtr<RenderPath>
		CreateRenderRoundRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect, float rx, float ry) = 0;

};