#pragma once
#include "Property/UIObject.h"

class RenderWindow;
class LayoutObject;
class LayoutWindow;
class UIWindow : public UIObject
{
public:
	UIWindow();
	~UIWindow();

	static SPtr<UIWindow> Create();	

	virtual SPtr<RenderObject> GetRenderObject() override;

	virtual SPtr<LayoutObject> GetLayoutObject() override;
public:
	SPtr<RenderWindow> GetRenderWindow();
private:
	RenderWindow* renderWindow() const;

	SPtr<RenderWindow> renderWindow_;
	SPtr<LayoutWindow> layoutWindow_;
};