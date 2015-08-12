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

	virtual SPtr<RenderObject> GetRenderObject() override;

	virtual SPtr<LayoutObject> GetLayoutObject() override;
public:
	SPtr<RenderWindow> GetRenderWindow();

	bool IsAddedToScreen() const { isAddedToScreen_; }
	void AddToScreen();
private:
	void InitRenderWindow();
	RenderWindow* renderWindow() const;

	SPtr<RenderWindow> renderWindow_;
	SPtr<LayoutWindow> layoutWindow_;

	bool isAddedToScreen_;
};