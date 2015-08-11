#include "stdafx.h"
#include "LayoutWindow.h"
#include "Property/UIWindow.h"
#include "Render/RenderWindow.h"
#include "LayoutContainer.h"

LayoutWindow::LayoutWindow()
{

}

LayoutWindow::~LayoutWindow()
{

}

void LayoutWindow::Layout()
{
	SPtr<UIWindow> owner = owner_.get();
	const SPtr<LayoutContainer>& container = owner->GetLayoutContainer();
	if (container)
		container->SetSize(size());//与窗口大小相同
}

void LayoutWindow::CalcLayoutBounds()
{
	SPtr<UIWindow> owner = owner_.get();
	SPtr<RenderWindow> window = owner->GetRenderWindow();

	base::Size sz(owner->GetPropertySize());	

	SetSize(sz);
 	window->SetSize(sz);
}
