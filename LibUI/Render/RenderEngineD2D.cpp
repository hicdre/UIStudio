#include "stdafx.h"
#include "RenderEngineD2D.h"
#include "RenderContextD2D.h"
#include "RenderBrushD2D.h"
#include "RenderPenD2D.h"
#include "RenderPathD2D.h"
#include "RenderPathBuilderD2D.h"
#include "RenderFontDW.h"

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

CComPtr<IDWriteFactory> RenderD2DEngine::GetDWriteFactory()
{
	return d2dEngineInstance->dwrite_factory_;
}

CComPtr<IDWriteFontCollection> RenderD2DEngine::GetSystemFontCollection()
{
	assert(dwrite_factory_);

	if (!system_font_collection_)
	{
		dwrite_factory_->GetSystemFontCollection(&system_font_collection_);
	}
	return system_font_collection_;
}

RenderD2DEngine::RenderD2DEngine()
{
	::CoInitialize(NULL);
	HRESULT hr = ::D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&factory_
		);
	assert(SUCCEEDED(hr));

	hr = ::DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&dwrite_factory_)
		);
	assert(SUCCEEDED(hr));

}

RenderD2DEngine::~RenderD2DEngine()
{
	factory_ = NULL;
	dwrite_factory_ = NULL;
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

SPtr<RenderPen> RenderD2DEngine::CreateRenderPen(const SPtr<RenderBrush>& brush, float width)
{
	SPtr<RenderBrushD2D> d2dBrush = brush;
	if (!d2dBrush)
		return NULL;
	return new RenderPenD2D(d2dBrush->GetRealBrush(), width);
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

SPtr<RenderPathBuilder> RenderD2DEngine::CreateRenderPathBuilder(const SPtr<RenderContext>& context)
{
	return new RenderPathBuilderD2D(factory_);
}

SPtr<RenderFont> RenderD2DEngine::CreateRenderFont(const std::wstring& family, AttributeFontWeight weight, AttributeFontStyle style, float size)
{
	CComPtr<IDWriteFontCollection> collection = GetSystemFontCollection();

	CComPtr<IDWriteFontFamily> fontFamily;
	CComPtr<IDWriteFont> font;
	//split by ',' and find first;
	UINT index = 0;
	BOOL exists = FALSE;
	collection->FindFamilyName(family.c_str(), &index, &exists);
	collection->GetFontFamily(index, &fontFamily);

	if (FAILED(fontFamily->GetFirstMatchingFont(DWFontWeight(weight), DWRITE_FONT_STRETCH_NORMAL, DWFontStyle(style), &font)))
		return NULL;

	return new RenderFontDW(font);
}

