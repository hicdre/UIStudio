#include "stdafx.h"
#include "LayoutManager.h"
#include "LayoutObject.h"
#include "Property/UIWindow.h"

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

void LayoutManager::OnWindowSizeChanged(const SPtr<UIObject>& obj)
{
	SPtr<UIWindow> window = obj;
	assert(window);	

	base::Size sz = window->GetLayoutObject()->CalcLayoutSize();
	window->GetLayoutObject()->SetSize(sz);
}
