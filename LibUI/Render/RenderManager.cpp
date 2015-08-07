#include "stdafx.h"
#include "RenderManager.h"
#include "Property/UIWindow.h"

RenderManager::RenderManager()
	: is_running_(false)
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

void RenderManager::RegiserWindow(const SPtr<UIWindow>& window)
{
	if (!is_running_) {
		pending_windows_.push_back(window->GetWeak<UIWindow>());
	}
	else {
		RunWindow(window);
	}
}

void RenderManager::UnRegiserWindow(const SPtr<UIWindow>& window)
{

}

void RenderManager::RunPendingWindow()
{
	is_running_ = true;
	for (const WPtr<UIWindow>& window : pending_windows_)
	{
		SPtr<UIWindow> w = window.get();
		RunWindow(w);
	}
	pending_windows_.clear();
}

void RenderManager::RunWindow(const SPtr<UIWindow>& window)
{
	//window->
}
