#include "stdafx.h"
#include "RenderWindow.h"
#include "Property/UIWindow.h"

const wchar_t* const kRenderWindowClassName = L"RenderWindow";

static const DWORD kWindowDefaultChildStyle =
WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
static const DWORD kWindowDefaultStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED;
static const DWORD kWindowDefaultExStyle = WS_EX_WINDOWEDGE;

using namespace base;

RenderWindow::RenderWindow()
	: hwnd_(NULL)
	, window_style_(0)
	, window_ex_style_(kWindowDefaultExStyle)
	, previous_cursor_(NULL)
	, class_style_(CS_DBLCLKS)
{

}

RenderWindow::~RenderWindow()
{
	if (::IsWindow(hwnd_)) {
		::SetWindowLongPtr(hwnd_, GWLP_USERDATA, NULL);
	}
}

void RenderWindow::InitClass()
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = kRenderWindowClassName;
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DROPSHADOW;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(COLOR_BACKGROUND));
	RegisterClassEx(&wc);
}

void RenderWindow::Render()
{
	//todo
}

void RenderWindow::OnVisibleChanged()
{
	Show(visible_ ? SW_SHOWNORMAL : SW_HIDE);
}

void RenderWindow::Init(HWND parent, const Rect& bounds)
{
	if (window_style_ == 0)
		window_style_ = parent ? kWindowDefaultChildStyle : kWindowDefaultStyle;

	int x, y, width, height;
	if (bounds.IsEmpty())
	{
		x = y = width = height = CW_USEDEFAULT;
	}
	else
	{
		x = bounds.x();
		y = bounds.y();
		width = bounds.width();
		height = bounds.height();
	}

	bool destroyed = false;
	HWND hwnd = CreateWindowEx(window_ex_style_, kRenderWindowClassName, NULL,
		window_style_, x, y, width, height,
		parent, NULL, NULL, this);

	//assert(hwnd_ && GetLastError() == 0);

	DWORD dwStyle = GetWindowLong(GWL_STYLE);
	SetWindowLong(GWL_STYLE, (dwStyle & ~WS_CAPTION));
}

// void RenderWindow::SetMessageHanler(MessageHandler* handler)
// {
// 	handler_ = handler;
// }
// 
// RenderWindow::MessageHandler* RenderWindow::GetMessageHanler()
// {
// 	return handler_;
// }

Rect RenderWindow::GetWindowScreenBounds() const
{
	RECT r;
	::GetWindowRect(hwnd(), &r);
	return Rect(r);
}

/*Rect RenderWindow::GetRestoredBounds() const
{

}*/

void RenderWindow::SetBounds(const Rect& bounds)
{
	LONG style = GetWindowLong(GWL_STYLE);
	if (style & WS_MAXIMIZE)
		SetWindowLong(GWL_STYLE, style & ~WS_MAXIMIZE);
	SetWindowPos(NULL, bounds.x(), bounds.y(), bounds.width(), bounds.height(),
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void RenderWindow::SetSize(const Size& size)
{
	SetWindowPos(NULL, 0, 0, size.width(), size.height(),
		SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
}

// void RenderWindow::CenterWindow(const Size& size)
// {
// 	HWND parent = GetParent();
// 	if (!IsWindow())
// 		parent = ::GetWindow(hwnd(), GW_OWNER);
// 	CenterAndSizeWindow(parent, hwnd(), size);
// }

void RenderWindow::Close()
{
	if (!IsWindow())
		return;  // No need to do anything.

	// Let's hide ourselves right away.
	Hide();

	::DestroyWindow(hwnd());
}

void RenderWindow::Show(int state)
{
	::ShowWindow(hwnd_, state);
}

bool RenderWindow::IsWindow()
{
	return ::IsWindow(hwnd_) == TRUE;
}

HWND RenderWindow::GetParent() const {
	return ::GetParent(hwnd());
}

LONG RenderWindow::GetWindowLong(int index)
{
	assert(::IsWindow(hwnd()));
	return ::GetWindowLong(hwnd(), index);
}

BOOL RenderWindow::GetWindowRect(RECT* rect) const
{
	return ::GetWindowRect(hwnd(), rect);
}

LONG RenderWindow::SetWindowLong(int index, LONG new_long)
{
	assert(::IsWindow(hwnd()));
	return ::SetWindowLong(hwnd(), index, new_long);
}

BOOL RenderWindow::SetWindowPos(HWND hwnd_after, int x, int y, int cx, int cy, UINT flags)
{
	assert(::IsWindow(hwnd()));
	return ::SetWindowPos(hwnd(), hwnd_after, x, y, cx, cy, flags);
}

BOOL RenderWindow::SetWindowPos(int x, int y)
{
	return SetWindowPos(NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

BOOL RenderWindow::MoveWindow(int x, int y, int width, int height)
{
	return MoveWindow(x, y, width, height, TRUE);
}

BOOL RenderWindow::MoveWindow(int x, int y, int width, int height, BOOL repaint)
{
	assert(::IsWindow(hwnd()));
	return ::MoveWindow(hwnd(), x, y, width, height, repaint);
}

int RenderWindow::SetWindowRgn(HRGN region, BOOL redraw)
{
	assert(::IsWindow(hwnd()));
	return ::SetWindowRgn(hwnd(), region, redraw);
}

BOOL RenderWindow::GetClientRect(RECT* rect) const
{
	assert(::IsWindow(hwnd()));
	return ::GetClientRect(hwnd(), rect);
}

void RenderWindow::Hide()
{
	if (IsWindow()) {
		// NOTE: Be careful not to activate any windows here (for example, calling
		// ShowWindow(SW_HIDE) will automatically activate another window).  This
		// code can be called while a window is being deactivated, and activating
		// another window will screw up the activation that is already in progress.
		SetWindowPos(NULL, 0, 0, 0, 0,
			SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE |
			SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER);

		//if (!GetParent())
		//	NotifyOwnedWindowsParentClosing();
	}
}

void RenderWindow::Active()
{
	if (IsMinimized())
		::ShowWindow(hwnd(), SW_RESTORE);
	::SetWindowPos(hwnd(), HWND_TOP, 0, 0, 0, 0,
		SWP_NOSIZE | SWP_NOMOVE);
	::SetForegroundWindow(hwnd());
}

bool RenderWindow::IsActive() const
{
	return ::GetActiveWindow() == hwnd();
}

void RenderWindow::Maximize()
{
	::SendMessage(hwnd(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
}

void RenderWindow::Minimize()
{
	::SendMessage(hwnd(), WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void RenderWindow::Restore()
{
	::SendMessage(hwnd(), WM_SYSCOMMAND, SC_RESTORE, 0);
}

bool RenderWindow::IsMaximized() const
{
	return !!::IsZoomed(hwnd());
}

bool RenderWindow::IsMinimized() const
{
	return !!::IsIconic(hwnd());
}

bool RenderWindow::IsVisible() const
{
	return !!::IsWindowVisible(hwnd());
}

LRESULT RenderWindow::OnWndProc(UINT message, WPARAM w_param, LPARAM l_param)
{
	LRESULT result = 0;

	// Handle the message if it's in our message map; otherwise, let the system
	// handle it.
	if (!ProcessWindowMessage(hwnd_, message, w_param, l_param, result))
		result = DefWindowProc(hwnd_, message, w_param, l_param);

	return result;
}

LRESULT CALLBACK RenderWindow::WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param)
{
	if (message == WM_NCCREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(l_param);
		RenderWindow* window = reinterpret_cast<RenderWindow*>(cs->lpCreateParams);
		assert(window);
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->hwnd_ = hwnd;
		return TRUE;
	}

	RenderWindow* window = reinterpret_cast<RenderWindow*>(
		::GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (!window)
		return 0;

	if (message == WM_PAINT)
		window->Render();

	return window->OnWndProc(message, w_param, l_param);
}

BOOL RenderWindow::ProcessWindowMessage(HWND window, UINT message, WPARAM w_param, LPARAM l_param, LRESULT& result)
{
	return FALSE;
}

void RenderWindow::SetCursor(HCURSOR cursor)
{
	if (cursor)
	{
		previous_cursor_ = ::SetCursor(cursor);
	}
	else if (previous_cursor_)
	{
		::SetCursor(previous_cursor_);
		previous_cursor_ = NULL;
	}
}

void RenderWindow::InvalidateRect(const Rect& r)
{
	::InvalidateRect(hwnd_, &r.ToRECT(), FALSE);
}

void RenderWindow::SetFocus()
{
	::SetFocus(hwnd_);
}

bool RenderWindow::IsFocused()
{
	return ::GetFocus() == hwnd_;
}

void RenderWindow::SetCaptured()
{
	::SetCapture(hwnd_);
}