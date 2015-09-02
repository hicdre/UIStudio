#include "stdafx.h"
#include "RenderTextLayoutDW.h"

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
