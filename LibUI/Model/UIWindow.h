#pragma once
#include "Model/UIObject.h"

class RenderWindow;
class LayoutObject;
class UIWindow : public UIObject
{
public:
	UIWindow();
	~UIWindow();	

	static SPtr<UIWindow> Create();

	virtual SPtr<RenderObject> GetRenderObject() override;

	virtual SPtr<LayoutObject> GetLayoutObject() override;
	virtual SPtr<LayoutContainer> GetLayoutContainer() override;
public:
	SPtr<RenderWindow> GetRenderWindow();
		
private:
	base::Size CalcWindowSize();
	void InitRenderWindow();
	RenderWindow* renderWindow() const;

	SPtr<RenderWindow> renderWindow_;
	SPtr<LayoutContainer> layoutContainer_;	
};