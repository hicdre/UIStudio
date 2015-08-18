#pragma once
#include "Base/object.h"
#include "Base/Geom/rect.h"
#include "Base/color.h"
#include "Render/RenderPaintServer.h"
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
	virtual base::Rect GetLocalBounds() = 0;

	base::Rect GetBounds() { return base::Rect(x(), y(), width(), height()); }
	float x() const { return anchor_.x(); }
	float y() const { return anchor_.y(); }
	float width() { return  GetLocalBounds().width(); }
	float height() { return GetLocalBounds().height(); }
	base::Size size() { return GetLocalBounds().size(); }

// 	void SetBounds(int x, int y, int width, int height);
// 	void SetBoundsRect(const base::Rect& bounds);
// 	void SetSize(const base::Size& size);
	void SetAnchorPosition(const base::Point& position);
	void SetAnchorPosition(int x, int y);
	void SetAnchorX(int x);
	void SetAnchorY(int y);

	base::Rect ConvertRectFromChild(RenderObject* child, const base::Rect& r);
	
	//set filled image	
	void SetFilledColor(base::Color color);
	void SetFilledNone();
	SPtr<RenderPaintServer> GetFillServer();

	void SetRenderObjectDirty(bool dirty);
	bool IsRenderObjectDirty() const;
	
protected:
	WPtr<UIObject> owner_;
	bool visible_;
	
	base::PointF anchor_;	

	WPtr<RenderObject> parent_;
	std::vector<SPtr<RenderObject>> childs_;
	base::Color color_;
	bool isRenderObjectDirty_;

	SPtr<RenderPaintServer> fillServer_;
};