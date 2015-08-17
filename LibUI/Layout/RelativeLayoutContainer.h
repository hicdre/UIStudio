#pragma once
#include "Layout/LayoutContainer.h"

class RelativeLayoutChild;
class RelativeLayoutContainer : public LayoutContainer
{
public:
	RelativeLayoutContainer();
	~RelativeLayoutContainer();

	virtual void Layout() override;

	virtual void GetChilds(std::vector<SPtr<LayoutObject>>& childs) override;
	virtual uint32_t GetChildCount() override;
	virtual void OnChildLayoutChanged(const SPtr<LayoutChild>& child) override;


	void GetRelativeChilds(std::vector<SPtr<RelativeLayoutChild>>& childs);
private:
	std::vector<SPtr<RelativeLayoutChild>> childs_;
};