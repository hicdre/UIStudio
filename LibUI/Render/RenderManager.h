#pragma once
#include "Delegate/Delegate.h"

class UIObject;
class RenderWindow;
class RenderObject;
class UIWindow;
class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	static RenderManager* Get();

	void Run();

	void AddWindow(const SPtr<UIWindow>& window);
	void OnWindowVisibleChanged(const SPtr<UIWindow>& obj);
private:
	bool is_running_;
	std::vector<WPtr<UIWindow>> pending_windows_;
};