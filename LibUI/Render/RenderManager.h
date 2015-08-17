#pragma once
#include "Delegate/Delegate.h"

class UIObject;
class RenderWindow;
class RenderObject;
class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	static RenderManager* Get();	

	void OnWindowVisibleChanged(const SPtr<UIObject>& obj);
private:
	
};