#include "stdafx.h"
#include "RenderEngineD2D.h"
#include "RenderContextD2D.h"
#include "RenderBrushD2D.h"
#include "RenderPathD2D.h"

#include "RenderWindow.h"

static RenderD2DEngine* d2dEngineInstance = NULL;

void RenderD2DEngine::Init()
{
	d2dEngineInstance = new RenderD2DEngine;
}

void RenderD2DEngine::Uninit()
{
	if (d2dEngineInstance)
	{
		delete d2dEngineInstance;
		d2dEngineInstance = NULL;
	}
}

RenderD2DEngine* RenderD2DEngine::Get()
{
	assert(d2dEngineInstance);
	return d2dEngineInstance;
}

CComPtr<ID2D1Factory> RenderD2DEngine::GetD2DFactory()
{
	return d2dEngineInstance->factory_;
}

RenderD2DEngine::RenderD2DEngine()
{
	::CoInitialize(NULL);
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&factory_
		);
	assert(SUCCEEDED(hr));
}

RenderD2DEngine::~RenderD2DEngine()
{
	::CoUninitialize();
}

SPtr<RenderContext> RenderD2DEngine::CreateRenderContext(const SPtr<RenderWindow>& window)
{
	CComPtr<ID2D1HwndRenderTarget> target;
	base::Rect rect = window->GetWindowScreenBounds();
	HRESULT hr = factory_->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
		window->hwnd(),
		D2D1::SizeU(rect.width(), rect.height())
		),
		&target
		);
	if (SUCCEEDED(hr))
	{
		return new RenderContextD2D(target);
	}
	assert(0);
	return nullptr;
}


SPtr<RenderBrush> RenderD2DEngine::CreateRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color)
{
	CComPtr<ID2D1RenderTarget> renderTarget = D2DGetTargetFromContext(context);
	if (!renderTarget)
		return NULL;

	CComPtr<ID2D1SolidColorBrush> brush;
	if (SUCCEEDED(renderTarget->CreateSolidColorBrush(D2DColor(color), &brush)))
		return new RenderBrushD2D(brush);
	return NULL;
}

SPtr<RenderPath> RenderD2DEngine::CreateRenderRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect)
{
	CComPtr<ID2D1RectangleGeometry> geometry;
	if (SUCCEEDED(factory_->CreateRectangleGeometry(D2DRect(rect), &geometry)))
		return new RenderPathD2D(geometry);
	return NULL;
}

SPtr<RenderPath> RenderD2DEngine::CreateRenderRoundRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect, float rx, float ry)
{
	CComPtr<ID2D1RoundedRectangleGeometry> geometry;
	if (SUCCEEDED(factory_->CreateRoundedRectangleGeometry(D2DRoundRect(rect, rx, ry), &geometry)))
		return new RenderPathD2D(geometry);
	return NULL;
}


