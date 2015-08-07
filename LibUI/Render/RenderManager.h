#pragma once
#include "Delegate/Delegate.h"

class UIWindow;
class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	static RenderManager* Get();

	void RegiserWindow(const SPtr<UIWindow>& window);
	void UnRegiserWindow(const SPtr<UIWindow>& window);

	void RunPendingWindow();
private:
	void RunWindow(const SPtr<UIWindow>& window);
	bool is_running_;
	std::vector<WPtr<UIWindow>> pending_windows_;
};