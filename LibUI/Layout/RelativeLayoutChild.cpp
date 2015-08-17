#include "stdafx.h"
#include "RelativeLayoutChild.h"

RelativeLayoutChild::RelativeLayoutChild()
{

}

RelativeLayoutChild::~RelativeLayoutChild()
{

}

base::Size RelativeLayoutChild::CalcLayoutSize()
{
	return LayoutObject::CalcLayoutSize();
}

void RelativeLayoutChild::OnContainerSizeChanged()
{
	//判断长宽是否为百分数
}
