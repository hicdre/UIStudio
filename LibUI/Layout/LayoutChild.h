#pragma once
#include "Layout/LayoutObject.h"

class LayoutContainer;
class LayoutChild : public LayoutObject
{
public:
	LayoutChild();
	~LayoutChild();

	SPtr<LayoutContainer> GetParent() const;
	void SetParent(const SPtr<LayoutContainer>& parent);

	SPtr<LayoutContainer> GetChildContainer() const;
	void SetChildContainer(const SPtr<LayoutContainer>& container);
		
	virtual void Layout() override;
private:
	WPtr<LayoutContainer> parent_;
	SPtr<LayoutContainer> childContainer_;
};