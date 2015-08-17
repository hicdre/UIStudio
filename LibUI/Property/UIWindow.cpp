#include "stdafx.h"
#include "UIWindow.h"
#include "Render/RenderManager.h"
#include "Render/RenderWindow.h"
#include "Render/RenderEngine.h"
#include "Render/RenderRectangle.h"
#include "Layout/LayoutObject.h"
#include "Layout/LayoutManager.h"
#include <functional>


UIWindow::UIWindow()
	
{
	
}

UIWindow::~UIWindow()
{
	
}

SPtr<UIWindow> UIWindow::Create()
{
	SPtr<UIWindow> window(new UIWindow);
	window->EventPropertyVisibleChanged.AddF([](const SPtr<UIObject>& obj)
	{
		RenderManager::Get()->OnWindowVisibleChanged(obj);
	});		
	window->EventPropertySizeChanged.AddF([](const SPtr<UIObject>& obj)
	{
		LayoutManager::Get()->OnWindowSizeChanged(obj);
	});	
}

SPtr<RenderObject> UIWindow::GetRenderObject()
{
	return GetRenderWindow();
}

SPtr<LayoutObject> UIWindow::GetLayoutObject()
{
// 	if (!layoutWindow_)
// 	{
// 		layoutWindow_.reset(new LayoutWindow);
// 		layoutWindow_->Attatch(GetSelf<UIObject>());
// 	}
// 	return layoutWindow_;
	return NULL;
}

SPtr<RenderWindow> UIWindow::GetRenderWindow()
{
	if (!renderWindow_)
	{
		renderWindow_ = RenderEngine::NewRenderWindow(GetPropertySize());
		InitRenderWindow();
	}
	return renderWindow_;
}


void UIWindow::InitRenderWindow()
{
	//test
	base::Size sz(GetPropertySize());
	SPtr<RenderRectangle> background = RenderEngine::NewRenderRectangle(sz.width(), sz.height()/2, base::Color_Green);
	renderWindow_->AddChild(background);
	background->SetY(20);
}

RenderWindow* UIWindow::renderWindow() const
{
	return renderWindow_.get();
}
