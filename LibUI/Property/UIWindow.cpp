#include "stdafx.h"
#include "UIWindow.h"
#include "Render/RenderManager.h"
#include "Render/RenderWindow.h"

UIWindow::UIWindow()
{
	RenderManager::Get()->RegiserWindow(GetSelf<UIWindow>());
}

UIWindow::~UIWindow()
{
	RenderManager::Get()->UnRegiserWindow(GetSelf<UIWindow>());
}

void UIWindow::SetWindowSize(int w, int h)
{
	property_dict_.SetInteger("size.width", w);
	property_dict_.SetInteger("size.height", h);
	OnPropertyChanged("size");	
}

void UIWindow::ShowWindow(bool show)
{
	PropertyValue* val = NULL;
	if (!property_dict_.Get("visible", &val)) {
		property_dict_.SetBoolean("visible", show);
		OnPropertyChanged("visible");
		return;
	}
	
	if (!val->IsBoolValue()) {
		val->SetBoolValue(show);
		OnPropertyChanged("visible");
		return;
	}

	if (val->GetBoolValue() == show)
		return;
	val->SetBoolValue(show);
	OnPropertyChanged("visible");		
}

SPtr<RenderWindow>&& UIWindow::CreateRenderWindow()
{
	SPtr<RenderWindow> window(new RenderWindow);
	window->Attatch(GetSelf<PropertyObject>());
	return std::move(window);
}
