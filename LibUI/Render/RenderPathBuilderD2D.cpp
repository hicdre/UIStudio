#include "stdafx.h"
#include "RenderPathBuilderD2D.h"
#include "RenderPathD2D.h"
#include "RenderFontDW.h"

#include <vector>

RenderPathBuilderD2D::RenderPathBuilderD2D(const CComPtr<ID2D1Factory>& f)
	: factory_(f)
	, isFigureBegin_(false)	
{
	factory_->CreatePathGeometry(&path_);
	path_->Open(&sink_);
	isSinkOpen_ = true;
}

RenderPathBuilderD2D::~RenderPathBuilderD2D()
{
	if (isSinkOpen_ && sink_)
	{
		sink_->Close();
		isSinkOpen_ = false;
	}
}

SPtr<RenderPath> RenderPathBuilderD2D::GetPath()
{
	if (!sink_ || !path_)
		return NULL;
	EndFigure();
	sink_->Close();
	isSinkOpen_ = false;
	return new RenderPathD2D(path_);
}

void RenderPathBuilderD2D::BeginFigure()
{
	isFigureBegin_ = true;
}

void RenderPathBuilderD2D::EndFigure()
{
	if (isFigureBegin_)
		sink_->EndFigure(D2D1_FIGURE_END_CLOSED);
	isFigureBegin_ = false;
}

void RenderPathBuilderD2D::AddLine(const base::PointF& from, const base::PointF& to)
{
	EndFigure();

	sink_->BeginFigure(D2DPoint(from), D2D1_FIGURE_BEGIN_FILLED);
	sink_->AddLine(D2DPoint(to));
}

void RenderPathBuilderD2D::AddEllipse(const base::Rect& rc)
{
	EndFigure();
	//4段贝塞尔二次曲线
	// p0-------m0-------p1
	// |------------------|
	// m3----------------m1
	// |------------------|
	// p3-------m2-------p2
	base::PointF p0(rc.x(), rc.y());
	base::PointF p1(rc.right(), rc.y());
	base::PointF p2(rc.right(), rc.bottom());
	base::PointF p3(rc.x(), rc.bottom());
	base::PointF m0(rc.x() + rc.width() / 2.0f, rc.y());
	base::PointF m1(rc.right(), rc.y() + rc.height() / 2.0f);
	base::PointF m2(rc.x() + rc.width() / 2.0f, rc.y());
	base::PointF m3(rc.x(), rc.y() + rc.height() / 2.0f);
	
	sink_->BeginFigure(D2DPoint(m3), D2D1_FIGURE_BEGIN_FILLED);
	sink_->AddQuadraticBezier(D2DQuadBezier(p0, m0));
	sink_->AddQuadraticBezier(D2DQuadBezier(p1, m1));
	sink_->AddQuadraticBezier(D2DQuadBezier(p2, m2));
	sink_->AddQuadraticBezier(D2DQuadBezier(p3, m3));

	EndFigure();
}

void RenderPathBuilderD2D::AddString(const std::wstring& text, const base::PointF& location, const SPtr<RenderFont>& font)
{
	SPtr<RenderFontDW> fontDw = font;
	if (!fontDw)
		return;

	CComPtr<IDWriteFontFace> fontFace = fontDw->GetFontFace();
	if (!fontFace)
		return;

	EndFigure();

	std::vector<uint32> codePoints;
	codePoints.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		codePoints[i] = text[i];
	}

	std::vector<uint16> glyphIndices;
	glyphIndices.resize(text.size());
	fontFace->GetGlyphIndicesW(&codePoints[0], codePoints.size(), &glyphIndices[0]);

	sink_->BeginFigure(D2DPoint(location), D2D1_FIGURE_BEGIN_FILLED);
	float fontDp = font->GetSize() / 96.0/*dpi*/ * 72/*1dp = 1/96 inch*/;
	fontFace->GetGlyphRunOutline(fontDp,
		&glyphIndices[0], //字型
		NULL, NULL, glyphIndices.size(),
		FALSE,
		FALSE, //从右到左
		sink_);

	EndFigure();
	
}

void RenderPathBuilderD2D::AddChar(uint32 codePoint, const base::PointF& location, const SPtr<RenderFont>& font)
{
	SPtr<RenderFontDW> fontDw = font;
	if (!fontDw)
		return;

	CComPtr<IDWriteFontFace> fontFace = fontDw->GetFontFace();
	if (!fontFace)
		return;

	EndFigure();
	
	uint16 glyphIndices[1]; 
	uint32 codePoints[1] = { codePoint };
	fontFace->GetGlyphIndicesW(codePoints, 1, glyphIndices);

	sink_->BeginFigure(D2DPoint(location), D2D1_FIGURE_BEGIN_FILLED);
	float fontDp = font->GetSize() / 96.0/*dpi*/ * 72/*1dp = 1/96 inch*/;
	fontFace->GetGlyphRunOutline(fontDp,
		glyphIndices, //字型
		NULL, NULL, 1,
		FALSE,
		FALSE, //从右到左
		sink_);

	EndFigure();
}

void RenderPathBuilderD2D::PepareSink()
{
	if (!sink_)
		path_->Open(&sink_);
}
