#include "stdafx.h"
#include "RelativeLayoutContainer.h"
#include "RelativeLayoutChild.h"

RelativeLayoutContainer::RelativeLayoutContainer()
{

}

RelativeLayoutContainer::~RelativeLayoutContainer()
{

}

void RelativeLayoutContainer::Layout()
{
	for (auto item : childs_)
	{
		item->OnContainerSizeChanged();
	}
}

void RelativeLayoutContainer::GetChilds(std::vector<SPtr<LayoutObject>>& childs)
{
	for (auto item : childs_)
	{
		childs.push_back(item);
	}
}

uint32_t RelativeLayoutContainer::GetChildCount()
{
	return childs_.size();
}

void RelativeLayoutContainer::OnChildLayoutChanged(const SPtr<LayoutChild>& child)
{
	//相对布局，子大小变化无需处理
}

void RelativeLayoutContainer::GetRelativeChilds(std::vector<SPtr<RelativeLayoutChild>>& childs)
{
	childs = childs_;
}
