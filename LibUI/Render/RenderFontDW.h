#pragma once
#include "Render/RenderFont.h"
#include "Render/RenderD2DUtils.h"

class RenderFontDW : public RenderFont
{
public:
	RenderFontDW(const CComPtr<IDWriteFont>& font);
	~RenderFontDW();

	virtual float GetSize() override;

	virtual void AddStringToPath(const SPtr<RenderContext>& renderer, const SPtr<RenderPath>& path, const std::wstring& text, const base::PointF& location) override;

	virtual float GetAscent(const SPtr<RenderContext>& renderer) override;

	virtual base::SizeF MeasureString(const SPtr<RenderContext>& renderer, const std::wstring& text) override;
protected:
	CComPtr<IDWriteFontFace> fontFace_;
	CComPtr<IDWriteFont> font_;
	float fontSize_;//绘制所需的px
};