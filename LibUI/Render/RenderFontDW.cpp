#include "stdafx.h"
#include "RenderFontDW.h"

RenderFontDW::RenderFontDW()
{

}

RenderFontDW::~RenderFontDW()
{

}

float RenderFontDW::GetSize()
{
	DWRITE_FONT_METRICS m = { 0 };
	fontFace_->GetMetrics(&m);
	return m.capHeight;
}

void RenderFontDW::AddStringToPath(const SPtr<RenderContext>& renderer, const SPtr<RenderPath>& path, const std::wstring& text, const base::PointF& location)
{

}

float RenderFontDW::GetAscent(const SPtr<RenderContext>& renderer)
{

}

base::SizeF RenderFontDW::MeasureString(const SPtr<RenderContext>& renderer, const std::wstring& text)
{

}
