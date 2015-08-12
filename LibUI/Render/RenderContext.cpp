#include "stdafx.h"
#include "RenderContext.h"

ScopedRenderTransform::ScopedRenderTransform(const SPtr<RenderContext>& context, const base::Matrix& m) : context_(context), m_(m)
{
	context_->Transform(m);
}

ScopedRenderTransform::~ScopedRenderTransform()
{
	context_->Transform(m_.Invert());
}
