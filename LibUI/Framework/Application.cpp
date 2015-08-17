#include "stdafx.h"
#include "Application.h"
#include "Base/utils.h"
#include "Render/RenderManager.h"
#include "Render/RenderWindow.h"
#include "Render/RenderEngine.h"
#include <cassert>
#include <gdiplus.h>
// #include "framework/widget.h"
// #include "utils/utils.h"
// #include "style/style_property.h"
// #include "render/render_include.h"


static const wchar_t kMessageWndClass[] = L"DuiFramework.MessageWindow";
static const wchar_t kWndClass[] = L"DuiFramework.Window";

static const int kMsgHaveWork = WM_USER + 1;

Application* gApplication = NULL;

Application::Application()
{
		
}

Application::~Application()
{

}

void Application::InitInstance()
{
	gApplication = new Application;
	gApplication->Init();
}

void Application::UninitInstance()
{
	if (gApplication)
	{
		gApplication->UnInit();
		delete gApplication;
	}		
	gApplication = NULL;
}	

void Application::Quit()
{
	::PostQuitMessage(0);
}

std::wstring Application::GetAppPath()
{
	return gApplication->app_path_;
}

void Application::Run()
{
	if (gApplication)
	{
		gApplication->InternalRun();
	}
}

void Application::InternalRun()
{	
	//RenderManager::Get()->RunPendingWindow();
	for (;;) {
		// If we do any work, we may create more messages etc., and more work may
		// possibly be waiting in another task group.  When we (for example)
		// ProcessNextWindowsMessage(), there is a good chance there are still more
		// messages waiting.  On the other hand, when any of these methods return
		// having done no work, then it is pretty unlikely that calling them again
		// quickly will find any work to do.  Finally, if they all say they had no
		// work, then it is a good time to consider sleeping (waiting) for more
		// work.

		ProcessNextWindowsMessage();

		if (should_quit_)
			break;

		WaitForWork();  // Wait (sleep) until we have work to do again.
	}

	UnInit();
}

void Application::Init()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken_, &gdiplusStartupInput, NULL);

	RenderEngine::InitEngine(RenderEngine::D2D);

	//InitStyleProperty();

	InitMessageWndClass();
	//Widget::InitClass();

	{
		app_path_.resize(MAX_PATH);
		DWORD size = GetModuleFileName(instance_, &app_path_[0], MAX_PATH);
		app_path_.resize(size);
	}
}


void Application::UnInit()
{
	//Font::UnInitFont();
	RenderEngine::UninitEngine();
		
	//RenderEngine::UnintEngine();
	Gdiplus::GdiplusShutdown(gdiplusToken_);
}


void Application::InitMessageWndClass()
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProcThunk;
	wc.hInstance = utils::GetModuleFromAddress(wc.lpfnWndProc);
	wc.lpszClassName = kMessageWndClass;
	instance_ = wc.hInstance;
	RegisterClassEx(&wc);

	message_hwnd_ =
		::CreateWindow(kMessageWndClass, 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, instance_, 0);
}

	

LRESULT CALLBACK Application::WndProcThunk(
	HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	LRESULT rv = 0;
	__try {
		switch (message) {
		case kMsgHaveWork:
			reinterpret_cast<Application*>(wparam)->HandleWorkMessage();
			break;
		case WM_TIMER:
			reinterpret_cast<Application*>(wparam)->HandleTimerMessage();
			break;
		}
		rv = DefWindowProc(hwnd, message, wparam, lparam);
	}
	__except (EXCEPTION_CONTINUE_SEARCH) {
	}
	return rv;
}

LRESULT CALLBACK Application::WndProcNormal(
	HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	LRESULT rv = 0;
	__try {
		//获取window节点
	}
	__except (EXCEPTION_CONTINUE_SEARCH) {
	}
	return rv;
}

void Application::HandleWorkMessage()
{

}

void Application::HandleTimerMessage()
{

}

bool Application::ProcessNextWindowsMessage()
{
	bool sent_messages_in_queue = false;
	DWORD queue_status = GetQueueStatus(QS_SENDMESSAGE);
	if (HIWORD(queue_status) & QS_SENDMESSAGE)
		sent_messages_in_queue = true;

	MSG msg;
	if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		return sent_messages_in_queue;

	if (WM_QUIT == msg.message) {
		// Repost the QUIT message so that it will be retrieved by the primary
		// GetMessage() loop.
		should_quit_ = true;
		PostQuitMessage(static_cast<int>(msg.wParam));
		return false;
	}

	// Todo: While running our main message pump, we discard kMsgHaveWork messages.
	if (msg.message == kMsgHaveWork && msg.hwnd == message_hwnd_)
		return true;

	if (CallMsgFilter(const_cast<MSG*>(&msg), kMessageFilterCode))
		return true;

	TranslateMessage(&msg);
	DispatchMessage(&msg);
	return true;
}

void Application::WaitForWork()
{
	DWORD result;
	result = MsgWaitForMultipleObjectsEx(0, NULL, INFINITE, QS_ALLINPUT,
		MWMO_INPUTAVAILABLE);

	if (WAIT_OBJECT_0 == result) {
		// A WM_* message is available.
		// If a parent child relationship exists between windows across threads
		// then their thread inputs are implicitly attached.
		// This causes the MsgWaitForMultipleObjectsEx API to return indicating
		// that messages are ready for processing (Specifically, mouse messages
		// intended for the child window may appear if the child window has
		// capture).
		// The subsequent PeekMessages call may fail to return any messages thus
		// causing us to enter a tight loop at times.
		// The WaitMessage call below is a workaround to give the child window
		// some time to process its input messages.
		MSG msg = { 0 };
		DWORD queue_status = GetQueueStatus(QS_MOUSE);
		if (HIWORD(queue_status) & QS_MOUSE &&
			!PeekMessage(&msg, NULL, WM_MOUSEFIRST, WM_MOUSELAST, PM_NOREMOVE)) {
			WaitMessage();
		}
		return;
	}
}

// 	ResourceLoader* Application::GetResourceLoader()
// 	{
// 		if (!resource_loader_.get()) {
// 			resource_loader_.reset(new ResourceLoader);
// 		}
// 		return resource_loader_.get();
// 	}



