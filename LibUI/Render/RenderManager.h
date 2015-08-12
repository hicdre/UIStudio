#pragma once
#include "Delegate/Delegate.h"

class UIWindow;
class RenderWindow;
class RenderObject;
class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	static RenderManager* Get();

	void ShowWindow(const SPtr<UIWindow>& window);	

	void RunPendingWindow();
private:
	void RunWindow(const SPtr<UIWindow>& window);
	bool is_running_;
	std::vector<WPtr<UIWindow>> pending_windows_;

	std::vector<SPtr<RenderObject>> render_objects_;
};