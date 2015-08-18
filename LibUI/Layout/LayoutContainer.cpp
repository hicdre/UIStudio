#include "stdafx.h"
#include "LayoutContainer.h"
#include "Model/UIObject.h"
#include "Model/UIObjectCollection.h"


LayoutContainer::LayoutContainer(LayoutContainerType type)
	: type_(type)	
	, isNeedLayout_(true)
{
	
}

LayoutContainer::~LayoutContainer()
{

}

void LayoutContainer::Attatch(const SPtr<UIObjectCollection>& children)
{
	children_ = children;
	//注册集合变化事件
	//children->EventOnChildChanged
	isNeedLayout_ = true;
}

void LayoutContainer::SetNeedsLayout()
{
	isNeedLayout_ = true;
}
