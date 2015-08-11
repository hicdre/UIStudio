#include "stdafx.h"
#include "UIWindow.h"
#include "Render/RenderManager.h"
#include "Render/RenderWindow.h"
#include "Layout/LayoutObject.h"
#include "Layout/LayoutWindow.h"

UIWindow::UIWindow()
{
	
}

UIWindow::~UIWindow()
{
	RenderManager::Get()->UnRegiserWindow(GetSelf<UIWindow>());
}


SPtr<UIWindow> UIWindow::Create()
{
	SPtr<UIWindow> window(new UIWindow);
	RenderManager::Get()->RegiserWindow(window);
	return window;
}

SPtr<RenderObject> UIWindow::GetRenderObject()
{
	return GetRenderWindow();
}

SPtr<LayoutObject> UIWindow::GetLayoutObject()
{
	if (!layoutWindow_)
	{
		layoutWindow_.reset(new LayoutWindow);
		layoutWindow_->Attatch(GetSelf<UIObject>());
	}
	return layoutWindow_;
}

SPtr<RenderWindow> UIWindow::GetRenderWindow()
{
	if (!renderWindow_)
	{
		renderWindow_.reset(new RenderWindow);
		renderWindow_->Init(NULL, base::Rect(100, 100));
		renderWindow_->Attatch(GetSelf<UIObject>());
	}
	return renderWindow_;
}

RenderWindow* UIWindow::renderWindow() const
{
	return renderWindow_.get();
}
