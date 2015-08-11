#pragma once
#include "Base/object.h"
#include <string>

class UIObject;
class RenderObject : public Object
{
public:
	RenderObject();
	~RenderObject();

	virtual void Render();
	
	void Attatch(const SPtr<UIObject>& object);
	void Detach();

	SPtr<UIObject> GetUIObject();

	virtual void OnVisibleChanged();
private:
	void OnPropertyVisibleChangedInternal(const SPtr<UIObject>& obj);

protected:
	WPtr<UIObject> owner_;
	bool visible_;
};