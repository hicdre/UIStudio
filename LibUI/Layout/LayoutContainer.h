#pragma once
#include "Layout/LayoutObject.h"

class LayoutChild;
class LayoutContainer : public LayoutObject
{
public:
	LayoutContainer();
	~LayoutContainer();

	virtual void GetChilds(std::vector<SPtr<LayoutObject>>& childs) = 0;
	virtual uint32_t GetChildCount() = 0;

	virtual void OnChildLayoutChanged(const SPtr<LayoutChild>& child) = 0;
};