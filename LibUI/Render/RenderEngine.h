#pragma once
#include "Base/object.h"
#include "Base/Geom/size.h"
#include "Base/color.h"
#include "Render/RenderBrush.h"

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

	static SPtr<RenderRectangle>
		NewRenderRectangle(int width, int height, base::Color color);

	static SPtr<RenderBrush>
		NewRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color);
public:
	virtual SPtr<RenderContext>
		CreateRenderContext(const SPtr<RenderWindow>& window) = 0;

	virtual SPtr<RenderRectangle>
		CreateRenderRectangle(int width, int height, base::Color color) = 0;

	virtual SPtr<RenderBrush>
		CreateRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color) = 0;

};