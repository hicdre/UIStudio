// Demon.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Demon.h"
#include "LibUI/LibUI.h"



int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Application::InitInstance();

	SPtr<UIWindow> window = UIWindow::Create();

	window->SetWidth(AttributeLength::Pixel(200));
	window->SetHeight(AttributeLength::Pixel(300));
	{
		SPtr<UIRectangle> rc(new UIRectangle);
		rc->SetTranslateX(AttributeLength::Pixel(50));
		rc->SetTranslateY(AttributeLength::Percent(0.3f));
		rc->SetWidth(AttributeLength::Pixel(100));
		rc->SetHeight(AttributeLength::Pixel(200));
		rc->SetFill(AttributePaint::Color(base::Color_Green));
		rc->SetStroke(AttributePaint::Color(base::Color_Red));
		rc->SetStrokeWidth(4.0f);
		window->GetChildren()->Add(rc);
	}
	window->SetVisible(true);
	
	Application::Run();
	Application::UninitInstance();

}

