#include "stdafx.h"
#include "UIWindow.h"
#include "UIObjectCollection.h"
#include "Render/RenderManager.h"
#include "Render/RenderWindow.h"
#include "Render/RenderEngine.h"
#include "Render/RenderRectangle.h"
#include "Layout/LayoutObject.h"
#include "Layout/LayoutManager.h"
#include "Layout/RelativeLayoutContainer.h"
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
	RenderManager::Get()->AddWindow(window);
	return window;
}

SPtr<RenderObject> UIWindow::GetRenderObject()
{
	return GetRenderWindow();
}

SPtr<LayoutObject> UIWindow::GetLayoutObject()
{	
	return NULL;
}

SPtr<RenderWindow> UIWindow::GetRenderWindow()
{
	if (!renderWindow_ || IsRenderObjectNeedsUpdate())
	{		
		renderWindow_ = RenderEngine::NewRenderWindow(CalcWindowSize());
		InitRenderWindow();

		SetRenderObjectNeedsUpdate();
	}
	return renderWindow_;
}


void UIWindow::InitRenderWindow()
{
	//test
	//base::Size sz(GetPropertySize());
// 	SPtr<RenderRectangle> background = RenderEngine::NewRenderRectangle(sz.width(), sz.height()/2, base::Color_Green);
// 	renderWindow_->AddChild(background);
// 	background->SetY(20);
}

RenderWindow* UIWindow::renderWindow() const
{
	return renderWindow_.get();
}

SPtr<LayoutContainer> UIWindow::GetLayoutContainer()
{
	if (!layoutContainer_ || isLayoutContainerChanged_)
	{
		if (layoutContainerType_ == RelativeLayout)
		{
			layoutContainer_ = new RelativeLayoutContainer;			
		}			
	}
	return layoutContainer_;
}

base::Size UIWindow::CalcWindowSize()
{
	return base::Size(GetWidth()->GetPixel(), GetHeight()->GetPixel());
}
