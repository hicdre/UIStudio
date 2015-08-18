#include "stdafx.h"
#include "AttributePaint.h"
#include "UIObject.h"
#include "Render/RenderEngine.h"

AttributePaint::AttributePaint()
{

}

AttributePaint::~AttributePaint()
{

}


SPtr<AttributeColorPaint> AttributeColorPaint::NotSet()
{
	static SPtr<AttributeColorPaint> notSetColor(new AttributeColorPaint);
	return notSetColor;
}

AttributeColorPaint::AttributeColorPaint()
	: color_(base::Color_Black)
{

}

AttributeColorPaint::~AttributeColorPaint()
{

}

void AttributeColorPaint::SetColor(base::Color color)
{
	color_ = color;
}

base::Color AttributeColorPaint::GetColor() const
{
	return color_;
}

SPtr<RenderBrush> AttributeColorPaint::GetBrush(const SPtr<UIObject>& object, const SPtr<RenderContext>& context, float opacity, bool forStroke /*= false*/)
{
	int alpha = (int)((opacity * (ColorGetA(color_) / 255.0f)) * 255);

	return RenderEngine::NewRenderSolidBrush(context, base::ColorSetARGB(alpha, ColorGetR(color_), ColorGetG(color_), ColorGetB(color_)));
}
