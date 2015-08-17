#pragma once
#include "Render/RenderObject.h"
#include "Render/RenderD2DUtils.h"

template <class T>
class RenderObjectD2D : public T
{
public:
	RenderObjectD2D() {}
	~RenderObjectD2D() {}

	virtual void Render(const SPtr<RenderContext>& context) override
	{
		CComPtr<ID2D1RenderTarget> renderTarget = D2DGetTargetFromContext(context);
		if (!renderTarget)
			return;

		RenderFill(renderTarget);
	}

	virtual CComPtr<ID2D1Geometry> GetPath() = 0;

protected:
	void RenderFill(const CComPtr<ID2D1RenderTarget>& renderer)
	{
		CComPtr<ID2D1Geometry> path = GetPath();
		if (!path)
			return;

		CComPtr<ID2D1SolidColorBrush> brush;
		if (SUCCEEDED(renderer->CreateSolidColorBrush(D2DColor(color_), &brush)))
		{
			renderer->FillGeometry(path, brush);
		}
	}
};