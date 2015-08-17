#pragma once
#include "Base/object.h"

class UIObject;
class UIWindow;
class LayoutManager
{
public:
	LayoutManager();
	~LayoutManager();

	static LayoutManager* Get();

	void Layout(const SPtr<UIWindow>& window);
};