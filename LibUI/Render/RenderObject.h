#pragma once
#include "Base/object.h"
#include "Base/Geom/rect.h"
#include "Base/color.h"
#include <string>
#include <vector>

class UIObject;
class RenderContext;
class RenderObject : public Object
{
public:
	RenderObject();
	~RenderObject();

	void DoRender(const SPtr<RenderContext>& context);
	virtual void Render(const SPtr<RenderContext>& context) = 0;
	
	void Attatch(const SPtr<UIObject>& object);
	void Detach();

	SPtr<UIObject> GetUIObject();

	//
	SPtr<RenderObject> GetParent() const;
	void SetParent(const SPtr<RenderObject>& parent);
	const std::vector<SPtr<RenderObject>>& GetChilds() const { return childs_; }
	void AddChild(const SPtr<RenderObject>& child);
	void InsertChildAt(const SPtr<RenderObject>& child, int index);
	void InsertChildAfter(const SPtr<RenderObject>& child, const SPtr<RenderObject>& ref);
	SPtr<RenderObject> RemoveChildAt(int index);
	SPtr<RenderObject> RemoveChild(const SPtr<RenderObject>& child);
	SPtr<RenderObject> GetChildAt(int index);
	void RemoveAllChilds();
	int GetChildCounts() const { return childs_.size(); }
	

	//geometry
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

	base::Rect ConvertRectFromChild(RenderObject* child, const base::Rect& r);
	
	//set filled image
	void SetFilledColor(base::Color color);
private:
	virtual void OnSizeChanged();
	//virtual void OnVisibleChanged();
	//void OnPropertyVisibleChangedInternal(const SPtr<UIObject>& obj);

protected:
	WPtr<UIObject> owner_;
	bool visible_;

	base::Rect bounds_; //  µº Œª÷√

	WPtr<RenderObject> parent_;
	std::vector<SPtr<RenderObject>> childs_;

	base::Color color_;
};