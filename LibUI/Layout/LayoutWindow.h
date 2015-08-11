#pragma once
#include "Layout/LayoutObject.h"

class LayoutWindow : public LayoutObject
{
public:
	LayoutWindow();
	~LayoutWindow();

	virtual void Layout() override;
	virtual void CalcLayoutBounds() override;
};