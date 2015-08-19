#include "stdafx.h"
#include "RenderEngine.h"
#include "RenderWindow.h"
#include "RenderContext.h"
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


SPtr<RenderContext> RenderEngine::NewRenderContext(const SPtr<RenderWindow>& window)
{
	return RenderEngine::Get()->CreateRenderContext(window);
}


SPtr<RenderBrush> RenderEngine::NewRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color)
{
	return RenderEngine::Get()->CreateRenderSolidBrush(context, color);
}

SPtr<RenderPath> RenderEngine::NewRenderRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect)
{
	return RenderEngine::Get()->CreateRenderRectanglePath(context, rect);
}

SPtr<RenderPath> RenderEngine::NewRenderRoundRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect, float rx, float ry)
{
	return RenderEngine::Get()->CreateRenderRoundRectanglePath(context, rect, rx, ry);
}

SPtr<RenderPathBuilder> RenderEngine::NewRenderPathBuilder(const SPtr<RenderContext>& context)
{
	return RenderEngine::Get()->CreateRenderPathBuilder(context);
}
