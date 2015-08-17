#pragma once
#include "Base/object.h"

class UIObject;
class LayoutManager
{
public:
	LayoutManager();
	~LayoutManager();

	static LayoutManager* Get();

	void OnWindowSizeChanged(const SPtr<UIObject>& obj);
};