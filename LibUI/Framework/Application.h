#pragma once
#include <string>
#include <windows.h>


class Application
{
public:
	static void InitInstance();
	static void UninitInstance();	

	static void Run();

	//ImageStore* DefaultImageStore();

	//ResourceLoader* GetResourceLoader();

	static std::wstring GetAppPath();

	static void Quit();
private:
	Application();
	~Application();

	void Init();
	void UnInit();
	void InitMessageWndClass();
	void InternalRun();

	static LRESULT CALLBACK WndProcThunk(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK WndProcNormal(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	void HandleWorkMessage();
	void HandleTimerMessage();

	bool ProcessNextWindowsMessage();
	void WaitForWork();

	static const int kMessageFilterCode = 0x5001;

	HWND message_hwnd_;
	HINSTANCE instance_;

	std::wstring app_path_;
	bool should_quit_{ false };

	//scoped_ptr<ImageStore> image_store_;
	//scoped_ptr<ResourceLoader> resource_loader_;

	ULONG_PTR gdiplusToken_;
};
