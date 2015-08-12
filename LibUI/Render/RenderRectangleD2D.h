#pragma once
#include "Render/RenderRectangle.h"
#include "Render/RenderContextD2D.h"
#include "RenderD2DUtils.h"

class RenderRectangleD2D : public RenderRectangle
{
public:
	virtual void Render(const SPtr<RenderContext>& context) override
	{
		CComPtr<ID2D1HwndRenderTarget> renderTarget = D2DGetTargetFromContext(context);
		if (!renderTarget)
			return;

		CComPtr<ID2D1SolidColorBrush> brush;
		if (SUCCEEDED(renderTarget->CreateSolidColorBrush(D2DColor(color_), &brush)))
		{
			renderTarget->FillRectangle(D2D1::RectF(0, 0, width(), height()), brush);
		}
		
	}
};


