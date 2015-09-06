#pragma once
#include "Render/RenderTextLayout.h"
#include "Render/RenderD2DUtils.h"


class RenderTextLayoutDW : public RenderTextLayout
{
public:
	RenderTextLayoutDW(const std::wstring& text, const CComPtr<IDWriteTextLayout>& layout);
	~RenderTextLayoutDW();

	virtual void SetFontFamilyName(const std::wstring& name, const base::Range& range) override;

	virtual void SetFontSize(float size, const base::Range& range) override;

	virtual void SetFontWeight(AttributeFontWeight v, const base::Range& range) override;

	virtual void SetTextAnchor(AttributeTextAnchor v) override;

	virtual void SetFontStyle(AttributeFontStyle v, const base::Range& range) override;

	virtual base::Rect GetBounds() override;

	virtual void Draw(const SPtr<RenderContext>& context, const SPtr<RenderBrush>& brush, float x, float y) override;
private:
	std::wstring text_;
	CComPtr<IDWriteTextLayout> layout_;
};