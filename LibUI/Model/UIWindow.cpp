#include "stdafx.h"
#include "UIWindow.h"
#include "UIObjectCollection.h"
#include "Render/RenderManager.h"
#include "Render/RenderWindow.h"
#include "Render/RenderEngine.h"
#include "Layout/LayoutObject.h"
#include "Layout/LayoutManager.h"
#include "Layout/RelativeLayoutContainer.h"
#include <functional>


UIWindow::UIWindow()
	: x_(AttributeLength::Pixel(0))
	, y_(AttributeLength::Pixel(0))
	, width_(AttributeLength::Pixel(0))
	, height_(AttributeLength::Pixel(0))
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


SPtr<RenderPath> UIWindow::GetPath(const SPtr<RenderContext>& context)
{
	return NULL;
}

base::Rect UIWindow::GetBounds()
{	
	return CalcWindowBounds();
}

void UIWindow::Render(const SPtr<RenderContext>& context)
{
	RenderChildren(context);
}

SPtr<RenderWindow> UIWindow::GetRenderWindow()
{
	if (!renderWindow_ || IsPathDirty())
	{
		base::Rect bounds = CalcWindowBounds();
		if (!renderWindow_)
			renderWindow_ = RenderWindow::Create(GetSelf<UIWindow>());
		renderWindow_->SetBounds(bounds);
		SetPathDirty(false);
	}	
	return renderWindow_;
}

SPtr<AttributeLength> UIWindow::GetX() const
{
	return x_;
}

void UIWindow::SetX(const SPtr<AttributeLength>& v)
{
	if (x_->IsEqual(v.get()))
		return;
	x_ = v;
	SetPathDirty(true);
}

SPtr<AttributeLength> UIWindow::GetY() const
{
	return y_;
}

void UIWindow::SetY(const SPtr<AttributeLength>& v)
{
	if (y_->IsEqual(v.get()))
		return;
	y_ = v;
	SetPathDirty(true);
}

SPtr<AttributeLength> UIWindow::GetWidth() const
{
	return width_;
}

void UIWindow::SetWidth(const SPtr<AttributeLength>& v)
{
	if (width_->IsEqual(v.get()))
		return;
	width_ = v;
	SetPathDirty(true);
}

SPtr<AttributeLength> UIWindow::GetHeight() const
{
	return height_;
}

void UIWindow::SetHeight(const SPtr<AttributeLength>& v)
{
	if (height_->IsEqual(v.get()))
		return;
	height_ = v;
	SetPathDirty(true);
}

void UIWindow::InitRenderWindow()
{
	//test
// 	base::Size sz(CalcWindowSize());
// 	SPtr<RenderRectangle> background = RenderEngine::NewRenderRectangle(sz.width()/2, sz.height()/2, base::Color_Green);
// 	renderWindow_->AddChild(background);
// 	background->SetAnchorPosition(20,20);
}

RenderWindow* UIWindow::renderWindow() const
{
	return renderWindow_.get();
}

// SPtr<LayoutContainer> UIWindow::GetLayoutContainer()
// {
// 	if (!layoutContainer_ || isLayoutContainerChanged_)
// 	{
// 		if (GetLayoutContainerType() == RelativeLayout)
// 		{
// 			layoutContainer_ = new RelativeLayoutContainer;			
// 		}			
// 	}
// 	return layoutContainer_;
// }

base::Rect UIWindow::CalcWindowBounds()
{	
	RECT center_bounds = { 0 };
	HWND parent = renderWindow_ ? renderWindow_->GetParent() : NULL;
	if (parent) {
		// If there is a parent, center over the parents bounds.
		::GetWindowRect(parent, &center_bounds);
	}

	if (::IsRectEmpty(&center_bounds)) 
	{

		HMONITOR monitor = NULL;
		if (renderWindow_)
		{
			// No parent or no parent rect. Center over the monitor the window is on.
			monitor = MonitorFromWindow(renderWindow_->hwnd(), MONITOR_DEFAULTTONEAREST);
		}
		else
		{
			POINT pt = { 0, 0 };
			monitor = MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);
		}
		if (monitor) {
			MONITORINFO mi = { 0 };
			mi.cbSize = sizeof(mi);
			GetMonitorInfo(monitor, &mi);
			center_bounds = mi.rcWork;
		}
		else {
			assert(0);// << "Unable to get default monitor";
		}
		
	}
	base::Rect bounds(center_bounds.left, center_bounds.top, center_bounds.right - center_bounds.left, center_bounds.bottom - center_bounds.top);
	float x, y, w, h;
	x = AttributeLength::CalcFromBounds(x_, bounds.width());
	y = AttributeLength::CalcFromBounds(y_, bounds.height());
	w = AttributeLength::CalcFromBounds(width_, bounds.width());
	h = AttributeLength::CalcFromBounds(height_, bounds.height());
	return base::Rect(x, y, w, h);
}
