#include "stdafx.h"
#include "RenderEngineD2D.h"
#include "RenderWindow.h"
#include "RenderContextD2D.h"
#include "RenderRectangleD2D.h"

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

SPtr<RenderRectangle> RenderD2DEngine::CreateRenderRectangle(int width, int height, base::Color color)
{
	SPtr<RenderRectangle> rect(new RenderRectangleD2D());
	rect->SetSize(base::Size(width, height));
	rect->SetFilledColor(color);
	return rect;
}
