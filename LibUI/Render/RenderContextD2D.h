#pragma once
#include "Render/RenderContext.h"
#include <d2d1.h>
#include <atlbase.h>

class RenderWindow;


class RenderContextD2D : public RenderContext
{
public:
	RenderContextD2D(const CComPtr<ID2D1HwndRenderTarget>& target);
	~RenderContextD2D();

	virtual void Transform(const base::Matrix& m) override;

	virtual void FillPath(const SPtr<RenderBrush>& brush, const SPtr<RenderPath>& path) override;

	const CComPtr<ID2D1HwndRenderTarget> GetD2DTarget() const { return target_; }
private:
	CComPtr<ID2D1HwndRenderTarget> target_;
	base::Matrix currentTransform_;
};