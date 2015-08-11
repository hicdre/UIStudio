#pragma once
#include "Base/object.h"
#include "Base/Geom/rect.h"
#include "Delegate/Delegate.h"

class LayoutObject;
class UIObject;

struct ResizeEventArgs
{
	ResizeEventArgs(const base::Size& a, const base::Size& b)
		: originSize(a), newSize(b) {}
	base::Size originSize;
	base::Size newSize;
};
typedef Event<void(const SPtr<LayoutObject>&, const ResizeEventArgs&)> ResizeEvent;

class LayoutObject : public Object
{
public:
	LayoutObject();
	~LayoutObject();

	//ResizeEvent EventResize;

	void Attatch(const SPtr<UIObject>& object);
	void Detach();

	SPtr<LayoutObject> GetParent() const;
	void SetParent(const SPtr<LayoutObject>& parent);

	const base::Rect& bounds() const { return bounds_; }
	int x() const { return bounds_.x(); }
	int y() const { return bounds_.y(); }
	int width() const { return bounds_.width(); }
	int height() const { return bounds_.height(); }
	const base::Size& size() const { return bounds_.size(); }
	base::Rect GetLocalBounds() const;

	void SetBounds(int x, int y, int width, int height);
	void SetBoundsRect(const base::Rect& bounds);
	void SetSize(const base::Size& size);
	void SetPosition(const base::Point& position);
	void SetPosition(int x, int y);
	void SetX(int x);
	void SetY(int y);

	virtual void Layout() = 0;//设置children的位置
	virtual void CalcLayoutBounds() = 0;//设置自身的位置
protected:
	void OnPropertyLayoutChangedInternal(const SPtr<UIObject>&);
	
	WPtr<LayoutObject> parent_;
	WPtr<UIObject> owner_;
	base::Rect bounds_; // 实际位置
};
