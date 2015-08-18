#include "stdafx.h"
#include "RenderEngine.h"
#include "RenderWindow.h"
#include "RenderContext.h"
#include "RenderRectangle.h"
#include "RenderEngineD2D.h"



void RenderEngine::InitEngine(Type type)
{
	RenderWindow::InitClass();
	RenderD2DEngine::Init();
}

RenderEngine* RenderEngine::Get()
{
	return RenderD2DEngine::Get();
}

void RenderEngine::UninitEngine()
{
	RenderD2DEngine::Uninit();
}

SPtr<RenderWindow> RenderEngine::NewRenderWindow(const base::Size& sz)
{
	SPtr<RenderWindow> window(new RenderWindow);
	window->Init(NULL, base::Rect(sz.width(),sz.height()));
	return window;
}

SPtr<RenderContext> RenderEngine::NewRenderContext(const SPtr<RenderWindow>& window)
{
	return RenderEngine::Get()->CreateRenderContext(window);
}

SPtr<RenderRectangle> RenderEngine::NewRenderRectangle(int width, int height, base::Color color)
{

	return RenderEngine::Get()->CreateRenderRectangle(width, height, color);
}

SPtr<RenderBrush> RenderEngine::NewRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color)
{
	return RenderEngine::Get()->CreateRenderSolidBrush(context, color);
}
