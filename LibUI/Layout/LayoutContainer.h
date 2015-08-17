#pragma once
#include "Layout/LayoutObject.h"

class LayoutChild;
class UIObjectCollection;
class LayoutContainer : public LayoutObject
{
public:
	LayoutContainer(LayoutContainerType type);
	~LayoutContainer();

	LayoutContainerType GetType() const { return type_; }
	
	virtual void Layout() = 0;

	void SetNeedsLayout();
	bool IsNeedsLayout() const { return isNeedLayout_; }
	void Attatch(const SPtr<UIObjectCollection>& children);

protected:
	LayoutContainerType type_;	
	SPtr<UIObjectCollection> children_;
	bool isNeedLayout_;

};