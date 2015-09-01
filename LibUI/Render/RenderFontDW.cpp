#include "stdafx.h"
#include "RenderFontDW.h"
#include "RenderPathD2D.h"
#include "RenderEngineD2D.h"
#include <vector>

RenderFontDW::RenderFontDW(const CComPtr<IDWriteFont>& font)
	: font_(font)
{
	font_->CreateFontFace(&fontFace_);
}

RenderFontDW::~RenderFontDW()
{

}

float RenderFontDW::GetSize()
{
	return fontSize_;
// 	DWRITE_FONT_METRICS m = { 0 };
// 	fontFace_->GetMetrics(&m);
// 	return m.ascent + m.descent;
}

void RenderFontDW::AddStringToPath(const SPtr<RenderContext>& renderer, const SPtr<RenderPath>& path, const std::wstring& text, const base::PointF& location)
{
	SPtr<RenderPathD2D> d2dPath = path;
	if (!d2dPath)
		return;

	//wstring to utf32
	std::vector<uint32> codePoints;
	codePoints.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		codePoints[i] = text[i];
	}
	std::vector<uint16> glyphIndices;
	glyphIndices.resize(text.size());
	fontFace_->GetGlyphIndicesW(&codePoints[0], codePoints.size(), &glyphIndices[0]);

	CComPtr<ID2D1PathGeometry> textPath;
	{
		CComPtr<ID2D1SimplifiedGeometrySink> pathSink;
		if (FAILED(RenderD2DEngine::GetD2DFactory()->CreatePathGeometry(&textPath)))
			return;

		if (FAILED(textPath->Open((ID2D1GeometrySink**)&pathSink)))
			return;

		pathSink->BeginFigure(D2DPoint(location), D2D1_FIGURE_BEGIN_FILLED);
		float fontDp = fontSize_ / 96.0/*dpi*/ * 72/*1dp = 1/96 inch*/;
		fontFace_->GetGlyphRunOutline(fontDp,
			&glyphIndices[0], //×ÖÐÍ
			NULL, NULL, glyphIndices.size(),
			FALSE,
			FALSE, //´ÓÓÒµ½×ó
			pathSink);
		pathSink->EndFigure(D2D1_FIGURE_END_CLOSED);
		pathSink->Close();
	}
	
	{
		CComPtr<ID2D1Geometry> p;
		p = textPath;
		d2dPath->AddGeometry(p);
	}	
}

float RenderFontDW::GetAscent(const SPtr<RenderContext>& renderer)
{
	DWRITE_FONT_METRICS m = { 0 };
	fontFace_->GetMetrics(&m);
	return m.ascent;
}

base::SizeF RenderFontDW::MeasureString(const SPtr<RenderContext>& renderer, const std::wstring& text)
{
	CComPtr<IDWriteTextLayout> layout;
	CComPtr<IDWriteTextFormat> format;
	if (FAILED(RenderD2DEngine::GetDWriteFactory()->CreateTextLayout(text.c_str(), text.size(),
		format, 10000.0f, 10000.0f, &layout)))
		return base::SizeF();

	DWRITE_TEXT_METRICS m = { 0 };
	layout->GetMetrics(&m);
	return base::SizeF(m.width, m.height);
}
