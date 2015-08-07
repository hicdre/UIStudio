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


	SPtr<UIWindow> window(new UIWindow);

	window->SetWindowSize(200, 300);
	window->ShowWindow(true);

	Application::Run();
	Application::UninitInstance();

}

