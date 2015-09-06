#include "stdafx.h"
#include "RenderTextLayoutDW.h"
#include "RenderContextD2D.h"
#include "RenderBrushD2D.h"

RenderTextLayoutDW::RenderTextLayoutDW(const std::wstring& text, const CComPtr<IDWriteTextLayout>& layout)
	: text_(text), layout_(layout)
{

}

RenderTextLayoutDW::~RenderTextLayoutDW()
{

}

void RenderTextLayoutDW::SetFontFamilyName(const std::wstring& name, const base::Range& range)
{
	layout_->SetFontFamilyName(name.c_str(), DWTextRange(range));
}

void RenderTextLayoutDW::SetFontSize(float size, const base::Range& range)
{
	float fontDp = size / 96.0/*dpi*/ * 72/*1dp = 1/96 inch*/;
	layout_->SetFontSize(fontDp, DWTextRange(range));
}

void RenderTextLayoutDW::SetFontWeight(AttributeFontWeight v, const base::Range& range)
{
	layout_->SetFontWeight(DWFontWeight(v), DWTextRange(range));
}

void RenderTextLayoutDW::SetTextAnchor(AttributeTextAnchor v)
{
	layout_->SetTextAlignment(DWTextAlignment(v));
}

void RenderTextLayoutDW::SetFontStyle(AttributeFontStyle v, const base::Range& range)
{
	layout_->SetFontStyle(DWFontStyle(v), DWTextRange(range));
}

base::Rect RenderTextLayoutDW::GetBounds()
{
	DWRITE_TEXT_METRICS m = { 0 };
	layout_->GetMetrics(&m);
	return base::Rect(m.left, m.top, m.width, m.height);
}

void RenderTextLayoutDW::Draw(const SPtr<RenderContext>& context, const SPtr<RenderBrush>& brush, float x, float y)
{
	SPtr<RenderContextD2D> d2dContext = context;
	if (!d2dContext)
		return;
	CComPtr<ID2D1Brush> d2dBrush = RenderBrushD2D::Get(brush);
	CComPtr<ID2D1RenderTarget> target = d2dContext->GetD2DTarget();
	if (!d2dBrush || !target)
		return;
	target->DrawTextLayout(D2D1::Point2F(x, y), layout_, d2dBrush);
}
