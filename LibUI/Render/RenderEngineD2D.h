#pragma once
#include "Render/RenderEngine.h"
#include <d2d1.h>
#include <dwrite.h>
#include <atlbase.h>

class RenderD2DEngine : public RenderEngine
{
public:
	RenderD2DEngine();
	~RenderD2DEngine();

	virtual SPtr<RenderContext> CreateRenderContext(const SPtr<RenderWindow>& window) override;

	virtual SPtr<RenderBrush>
		CreateRenderSolidBrush(const SPtr<RenderContext>& context, base::Color color) override;

	virtual SPtr<RenderPen>
		CreateRenderPen(const SPtr<RenderBrush>& brush, float width) override;

	virtual SPtr<RenderPath>
		CreateRenderRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect) override;

	virtual SPtr<RenderPath>
		CreateRenderRoundRectanglePath(const SPtr<RenderContext>& context, const base::Rect& rect, float rx, float ry) override;
	
	virtual SPtr<RenderPathBuilder>
		CreateRenderPathBuilder(const SPtr<RenderContext>& context) override;

	virtual SPtr<RenderFont>
		CreateRenderFont(const std::wstring& family, AttributeFontWeight weight, AttributeFontStyle style, float size) override;
	static void Init();
	static void Uninit();
	static RenderD2DEngine* Get();
	static CComPtr<ID2D1Factory> GetD2DFactory();
	static CComPtr<IDWriteFactory> GetDWriteFactory();
private:
	CComPtr<IDWriteFontCollection> GetSystemFontCollection();
	CComPtr<ID2D1Factory> factory_;
	CComPtr<IDWriteFactory> dwrite_factory_;
	CComPtr<IDWriteFontCollection> system_font_collection_;
};