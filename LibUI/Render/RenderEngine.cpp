#include "stdafx.h"
#include "RenderEngine.h"
#include "RenderWindow.h"
#include "RenderContext.h"
#include "RenderRectangle.h"
#include "RenderEngineD2D.h"



static RenderEngine* engineInstance = NULL;

void RenderEngine::InitEngine(Type type)
{
	RenderWindow::InitClass();
	assert(!engineInstance);
	engineInstance = new RenderD2DEngine();
}

RenderEngine* RenderEngine::Get()
{
	return engineInstance;
}

void RenderEngine::UninitEngine()
{
	if (engineInstance)
	{
		delete engineInstance;
		engineInstance = NULL;
	}
}

SPtr<RenderWindow> RenderEngine::NewRenderWindow(const base::Size& sz)
{
	SPtr<RenderWindow> window(new RenderWindow);
	window->Init(NULL, base::Rect(sz.width(),sz.height()));
	return window;
}

SPtr<RenderContext> RenderEngine::NewRenderContext(const SPtr<RenderWindow>& window)
{
	assert(engineInstance);
	return engineInstance->CreateRenderContext(window);
}

SPtr<RenderRectangle> RenderEngine::NewRenderRectangle(int width, int height, base::Color color)
{
	assert(engineInstance);
	return engineInstance->CreateRenderRectangle(width, height, color);
}
