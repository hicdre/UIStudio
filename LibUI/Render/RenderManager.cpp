#include "stdafx.h"
#include "RenderManager.h"

#include "RenderWindow.h"
#include "Property/UIWindow.h"
#include "Layout/LayoutObject.h"

RenderManager::RenderManager()
	//: is_running_(false)
{

}

RenderManager::~RenderManager()
{

}

RenderManager* RenderManager::Get()
{
	static RenderManager inst;
	return &inst;
}

// void RenderManager::ShowWindow(const SPtr<UIWindow>& window)
// {
// 	if (!is_running_) {
// 		pending_windows_.push_back(window->GetWeak<UIWindow>());
// 	}
// 	else {
// 		RunWindow(window);
// 	}
// }
// 
// 
// void RenderManager::RunPendingWindow()
// {
// 	is_running_ = true;
// 	for (const WPtr<UIWindow>& window : pending_windows_)
// 	{
// 		SPtr<UIWindow> w = window.get();
// 		RunWindow(w);
// 	}
// 	pending_windows_.clear();
// }

void RenderManager::OnWindowVisibleChanged(const SPtr<UIObject>& obj)
{
	SPtr<UIWindow> window = obj;
	assert(window);
	if (window->GetPropertyVisible())
	{
		window->GetRenderWindow()->Show(SW_SHOWNORMAL);
	}
	else
	{
		window->GetRenderWindow()->Show(SW_HIDE);
	}
}
