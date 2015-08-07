#pragma once
#include "Property/PropertyObject.h"

class RenderWindow;
class UIWindow : public PropertyObject
{
public:
	UIWindow();
	~UIWindow();

	void SetWindowSize(int w, int h);
	void ShowWindow(bool show);

	SPtr<RenderWindow>&& CreateRenderWindow();
private:

};