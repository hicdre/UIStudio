#pragma once
#include "Model/UIVisualObject.h"
#include "Model/AttributeLength.h"

class UIRectangle : public UIVisualObject
{
public:
	UIRectangle();
	~UIRectangle();

	SPtr<AttributeLength> GetX() const;
	void SetX(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetY() const;
	void SetY(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetWidth() const;
	void SetWidth(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetHeight() const;
	void SetHeight(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetRadiusX() const;
	void SetRadiusX(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetRadiusY() const;
	void SetRadiusY(const SPtr<AttributeLength>& v);

	virtual SPtr<RenderPath> GetPath(const SPtr<RenderContext>& context) override;

	virtual base::Rect GetBounds() override;
protected:
	base::Rect CalcRect(float& rx, float& ry);	
	SPtr<AttributeLength> x_;
	SPtr<AttributeLength> y_;
	SPtr<AttributeLength> width_;
	SPtr<AttributeLength> height_;
	SPtr<AttributeLength> rx_;
	SPtr<AttributeLength> ry_;
	SPtr<RenderPath> renderPath_;
};