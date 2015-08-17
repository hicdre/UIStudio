#pragma once
#include "Layout/LayoutChild.h"

class RelativeLayoutContainer;
class RelativeLayoutChild : public LayoutChild
{
public:
	RelativeLayoutChild();
	~RelativeLayoutChild();

	virtual base::Size CalcLayoutSize() override;

	void OnContainerSizeChanged();
};