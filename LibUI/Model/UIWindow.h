#pragma once
#include "Model/UIVisualObject.h"

class RenderWindow;
class LayoutObject;
//UIContainer or UIGroup
class UIWindow : public UIVisualObject
{
public:
	UIWindow();
	~UIWindow();	

	static SPtr<UIWindow> Create();

	virtual SPtr<RenderPath> GetPath(const SPtr<RenderContext>& context) override;

	virtual base::Rect GetBounds() override;

	virtual void Render(const SPtr<RenderContext>& context) override;
public:
	SPtr<RenderWindow> GetRenderWindow();

	SPtr<AttributeLength> GetX() const;
	void SetX(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetY() const;
	void SetY(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetWidth() const;
	void SetWidth(const SPtr<AttributeLength>& v);

	SPtr<AttributeLength> GetHeight() const;
	void SetHeight(const SPtr<AttributeLength>& v);
		
private:
	base::Rect CalcWindowBounds();
	void InitRenderWindow();
	RenderWindow* renderWindow() const;

	SPtr<RenderWindow> renderWindow_;
	SPtr<LayoutContainer> layoutContainer_;	

	SPtr<AttributeLength> x_;
	SPtr<AttributeLength> y_;
	SPtr<AttributeLength> width_;
	SPtr<AttributeLength> height_;
};