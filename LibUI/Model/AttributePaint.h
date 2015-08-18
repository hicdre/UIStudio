#pragma once
#include "Model/UIObject.h"
#include "Base/color.h"
#include "Render/RenderBrush.h"

class AttributePaint : public Object
{
public:
	AttributePaint();
	~AttributePaint();

	virtual SPtr<RenderBrush> GetBrush(const SPtr<UIObject>& object, const SPtr<RenderContext>& context, float opacity, bool forStroke = false) = 0;
};

class AttributeColorPaint : public AttributePaint
{
public:
	static SPtr<AttributeColorPaint> NotSet();

	AttributeColorPaint();
	~AttributeColorPaint();

	void SetColor(base::Color color);
	base::Color GetColor() const;

	virtual SPtr<RenderBrush> GetBrush(const SPtr<UIObject>& object, const SPtr<RenderContext>& context, float opacity, bool forStroke = false) override;
private:
	base::Color color_;
};