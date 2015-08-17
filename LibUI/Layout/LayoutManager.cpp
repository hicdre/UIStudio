#include "stdafx.h"
#include "LayoutManager.h"
#include "LayoutObject.h"
#include "RelativeLayoutContainer.h"
#include "Property/UIWindow.h"
#include "Property/UIObjectCollection.h"

LayoutManager::LayoutManager()
{

}

LayoutManager::~LayoutManager()
{

}

LayoutManager* LayoutManager::Get()
{
	static LayoutManager inst;
	return &inst;
}

// void LayoutManager::OnWindowSizeChanged(const SPtr<UIObject>& obj)
// {
// 	SPtr<UIWindow> window = obj;
// 	assert(window);	
// 
// 	base::Size sz = window->GetLayoutObject()->CalcLayoutSize();
// 	window->GetLayoutObject()->SetSize(sz);
// }

void LayoutManager::Layout(const SPtr<UIWindow>& window)
{
	SPtr<LayoutContainer> container = window->GetLayoutContainer();
	if (container->GetType() == RelativeLayout)
	{
		SPtr<RelativeLayoutContainer> relativeContainer = container;
		SPtr<UIObjectCollection> children = window->GetChildren();
		relativeContainer->Attatch(children);
// 		for (auto child : *children.get())
// 		{
// 			relativeContainer->AddChild(child->GetLayoutObject());
// 		}
	}
}
