#include "stdafx.h"
#include "LayoutChild.h"
#include "LayoutContainer.h"

LayoutChild::LayoutChild()
{

}

LayoutChild::~LayoutChild()
{

}

SPtr<LayoutContainer> LayoutChild::GetParent() const
{
	return parent_.get();
}

void LayoutChild::SetParent(const SPtr<LayoutContainer>& parent)
{
	parent_.reset(parent);
}

SPtr<LayoutContainer> LayoutChild::GetChildContainer() const
{
	return childContainer_.get();
}

void LayoutChild::SetChildContainer(const SPtr<LayoutContainer>& container)
{
	childContainer_ = container;
}

void LayoutChild::Layout()
{
	if (SPtr<LayoutContainer> parent = GetParent())
		parent->OnChildLayoutChanged(GetSelf<LayoutChild>());
	if (childContainer_)
		childContainer_->SetBoundsRect(GetLocalBounds());
}
