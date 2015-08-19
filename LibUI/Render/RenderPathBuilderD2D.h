#pragma once
#include "Render/RenderPathBuilder.h"
#include "Render/RenderD2DUtils.h"

class RenderPathBuilderD2D : public RenderPathBuilder
{
public:
	RenderPathBuilderD2D(const CComPtr<ID2D1Factory>& f);
	~RenderPathBuilderD2D();

	virtual SPtr<RenderPath> GetPath() override;

	virtual void BeginFigure() override;
	virtual void EndFigure() override;

	virtual void AddLine(const base::PointF& from, const base::PointF& to) override;

	virtual void AddEllipse(const base::Rect& rc) override;
protected:
	void PepareSink();
	CComPtr<ID2D1Factory> factory_;
	CComPtr<ID2D1PathGeometry> path_;
	CComPtr<ID2D1GeometrySink> sink_;
	bool isFigureBegin_;
	bool isSinkOpen_;
};