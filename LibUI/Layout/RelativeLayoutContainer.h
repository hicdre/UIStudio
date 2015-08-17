#pragma once
#include "Layout/LayoutContainer.h"

class RelativeLayoutChild;
class UIObject;
class RelativeLayoutContainer : public LayoutContainer
{
public:
	RelativeLayoutContainer();
	~RelativeLayoutContainer();

	virtual void Layout() override;		
	
private:
	SPtr<UIObjectCollection> children_;
	
};