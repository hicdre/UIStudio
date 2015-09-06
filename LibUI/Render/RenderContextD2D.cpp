#include "stdafx.h"
#include "RenderContextD2D.h"
#include "RenderWindow.h"
#include "RenderD2DUtils.h"
#include "RenderBrushD2D.h"
#include "RenderPenD2D.h"
#include "RenderPathD2D.h"
#include "RenderEngineD2D.h"


RenderContextD2D::RenderContextD2D(const CComPtr<ID2D1RenderTarget>& target)
	: target_(target)
{
	target_->BeginDraw();
}

RenderContextD2D::~RenderContextD2D()
{
	target_->EndDraw();
}

base::Matrix RenderContextD2D::GetTransform()
{
	return currentTransform_;
}

void RenderContextD2D::SetTransform(const base::Matrix& m)
{
	currentTransform_ = m;
	target_->SetTransform(D2DMatrix(currentTransform_));
}

// void RenderContextD2D::StorkeRect(const base::Rect& rect, base::Color color, uint32 size)
// {
// 	CComPtr<ID2D1SolidColorBrush> brush;
// 	if (SUCCEEDED(target_->CreateSolidColorBrush(D2D1::ColorF(color), &brush)))
// 	{
// 		target_->DrawRectangle(D2D1::RectF(rect.x(), rect.y(), rect.right, rect.bottom()),
// 			brush, size);
// 	}	
// }
// 
// void RenderContextD2D::FillRect(const base::Rect& rect, base::Color color)
// {
// 	CComPtr<ID2D1SolidColorBrush> brush;
// 	if (SUCCEEDED(target_->CreateSolidColorBrush(D2D1::ColorF(color), &brush)))
// 	{
// 		target_->FillRectangle(D2D1::RectF(rect.x(), rect.y(), rect.right, rect.bottom()),
// 			brush);
// 	}
// }
// 
// void RenderContextD2D::PushState()
// {
// 	//target_->SaveDrawingState()
// }
// 
// void RenderContextD2D::PopState()
// {
// 
// }

void RenderContextD2D::Transform(const base::Matrix& m)
{
	currentTransform_.ConcatTransform(m);	
	target_->SetTransform(D2DMatrix(currentTransform_));
}

void RenderContextD2D::FillPath(const SPtr<RenderBrush>& brush, const SPtr<RenderPath>& path)
{
	SPtr<RenderBrushD2D> d2dBrush = brush;
	SPtr<RenderPathD2D> d2dPath = path;
	if (!d2dBrush || !d2dPath)
		return;

	target_->FillGeometry(d2dPath->GetRealPath(), d2dBrush->GetRealBrush());
}

void RenderContextD2D::DrawPath(const SPtr<RenderPen>& pen, const SPtr<RenderPath>& path)
{
	SPtr<RenderPenD2D> d2dPen = pen;
	SPtr<RenderPathD2D> d2dPath = path;
	if (!d2dPen || !d2dPath)
		return;

	CComPtr<ID2D1StrokeStyle> style;
	if (FAILED(RenderD2DEngine::GetD2DFactory()->CreateStrokeStyle(d2dPen->GetStrokeStyle(), NULL, 0, &style)))
		return;

	target_->DrawGeometry(d2dPath->GetRealPath(), d2dPen->GetRealBrush(), d2dPen->GetStrokeWidth(), style);
}

