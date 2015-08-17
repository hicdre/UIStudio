#include "stdafx.h"
#include "RenderObject.h"
#include "Property/UIObject.h"
#include "Base/Geom/matrix.h"
#include "Render/RenderContext.h"

using namespace base;

RenderObject::RenderObject()
	: visible_(false)
{

}

RenderObject::~RenderObject()
{

}

void RenderObject::DoRender(const SPtr<RenderContext>& context)
{
	Render(context);
	for (auto iter = childs_.begin(); iter != childs_.end(); iter++)
	{
		base::Matrix m;
		SPtr<RenderObject> child = *iter;
		ScopedRenderTransform t(context, m.Translate(child->x(), child->y()));
		child->DoRender(context);		
	}
}

void RenderObject::Attatch(const SPtr<UIObject>& object)
{
	owner_.reset(object);
// 	object->EventVisibleChanged.AddW(GetWeak<RenderObject>(),
// 		&RenderObject::OnPropertyVisibleChangedInternal);
// 	OnPropertyVisibleChangedInternal(object);
}

void RenderObject::Detach()
{
	owner_.reset();
}

SPtr<UIObject> RenderObject::GetUIObject()
{
	return owner_.get();
}

SPtr<RenderObject> RenderObject::GetParent() const
{
	return parent_.get();
}

void RenderObject::SetParent(const SPtr<RenderObject>& parent)
{
	parent_.reset(parent);
}

void RenderObject::AddChild(const SPtr<RenderObject>& child)
{
	childs_.push_back(child);
}

void RenderObject::InsertChildAt(const SPtr<RenderObject>& child, int index)
{	
	childs_.insert(childs_.begin() + index, child);
}

void RenderObject::InsertChildAfter(const SPtr<RenderObject>& child, const SPtr<RenderObject>& ref)
{
	for (auto iter = childs_.begin(); iter != childs_.end(); iter++)
	{
		if (*iter == ref)
		{
			childs_.insert(iter + 1, child);
			return;
		}
	}
}

SPtr<RenderObject> RenderObject::RemoveChildAt(int index)
{
	SPtr<RenderObject> obj = GetChildAt(index);
	if (obj)
		childs_.erase(childs_.begin() + index);
	return obj;
}

SPtr<RenderObject> RenderObject::RemoveChild(const SPtr<RenderObject>& child)
{
	for (auto iter = childs_.begin(); iter != childs_.end(); iter++)
	{
		if (*iter == child)
		{
			SPtr<RenderObject> obj = *iter;
			childs_.erase(iter);
			return obj;
		}
	}
	return nullptr;
}

SPtr<RenderObject> RenderObject::GetChildAt(int index)
{
	if (index < 0 || index >= childs_.size())
		return nullptr;
	return childs_[index];
}

void RenderObject::RemoveAllChilds()
{
	for (auto iter = childs_.begin(); iter != childs_.end(); iter++)
	{
		(*iter)->parent_.reset();
	}
	childs_.clear();
}

base::Rect RenderObject::GetLocalBounds() const
{
	return Rect(width(), height());
}

void RenderObject::SetBounds(int x, int y, int width, int height)
{
	SetBoundsRect(Rect(x, y, (std::max)(0, width), (std::max)(0, height)));
}

void RenderObject::SetBoundsRect(const base::Rect& bounds)
{
	if (bounds == bounds_) {
		return;
	}

	Rect prev = bounds_;
	bounds_ = bounds;
	if (prev.size() != size()) {
		// 		ResizeEventArgs args(prev.size(), size());
		// 		EventResize.Execute(GetSelf<LayoutObject>(), args);
		//Layout();
		OnSizeChanged();
	}
}

void RenderObject::SetSize(const base::Size& size)
{
	SetBounds(x(), y(), size.width(), size.height());
}

void RenderObject::SetPosition(const base::Point& position)
{
	SetBounds(position.x(), position.y(), width(), height());
}

void RenderObject::SetPosition(int x, int y)
{
	SetBounds(x, y, width(), height());
}

void RenderObject::SetX(int x)
{
	SetBounds(x, y(), width(), height());
}

void RenderObject::SetY(int y)
{
	SetBounds(x(), y, width(), height());
}

base::Rect RenderObject::ConvertRectFromChild(RenderObject* child, const base::Rect& r)
{
	return Rect(r.x() + child->x(), r.y() + child->y(), r.width(), r.height());
}

void RenderObject::SetFilledColor(base::Color color)
{
	color_ = color;
}

void RenderObject::OnSizeChanged()
{

}


// void RenderObject::OnPropertyVisibleChangedInternal(const SPtr<UIObject>& obj)
// {
// 	visible_ = obj->GetPropertyVisible();
// 	OnVisibleChanged();
// }
