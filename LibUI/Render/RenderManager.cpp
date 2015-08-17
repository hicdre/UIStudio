#include "stdafx.h"
#include "RenderManager.h"

#include "RenderWindow.h"
#include "Property/UIWindow.h"
#include "Layout/LayoutObject.h"

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

void RenderManager::AddWindow(const SPtr<UIWindow>& window)
{
	window->EventPropertyChanged.AddF([](const SPtr<UIObject>& obj, const std::string& name)
	{
		if (name == "visible")
		{
			RenderManager::Get()->OnWindowVisibleChanged(obj);
		}
	});
	if (!is_running_) {
		pending_windows_.push_back(window->GetWeak<UIWindow>());
	}
	else {
		OnWindowVisibleChanged(window);
	}
}
 
void RenderManager::Run()
{
	is_running_ = true;
	for (const WPtr<UIWindow>& window : pending_windows_)
	{
		SPtr<UIWindow> w = window.get();
		OnWindowVisibleChanged(w);
	}
	pending_windows_.clear();
}

void RenderManager::OnWindowVisibleChanged(const SPtr<UIWindow>& window)
{	
	if (window->IsVisible())
	{
		window->GetRenderWindow()->Show(SW_SHOWNORMAL);
	}
	else
	{
		window->GetRenderWindow()->Show(SW_HIDE);
	}
}
