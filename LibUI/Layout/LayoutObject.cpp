#include "stdafx.h"
#include "LayoutObject.h"
#include <algorithm>


using namespace base;

LayoutObject::LayoutObject()
{

}

LayoutObject::~LayoutObject()
{

}

base::Rect LayoutObject::GetLocalBounds() const
{
	return Rect(width(), height());
}

void LayoutObject::SetBounds(int x, int y, int width, int height)
{
	SetBoundsRect(Rect(x, y, (std::max)(0, width), (std::max)(0, height)));
}

void LayoutObject::SetBoundsRect(const base::Rect& bounds)
{
	if (bounds == bounds_) {
		return;
	}

	Rect prev = bounds_;
	bounds_ = bounds;
	if (prev.size() != size()) {
		ResizeEventArgs args(prev.size(), size());
		EventResize.Execute(GetSelf<LayoutObject>(), args);
	}
}

void LayoutObject::SetSize(const base::Size& size)
{
	SetBounds(x(), y(), size.width(), size.height());
}

void LayoutObject::SetPosition(const base::Point& position)
{
	SetBounds(position.x(), position.y(), width(), height());
}

void LayoutObject::SetPosition(int x, int y)
{
	SetBounds(x, y, width(), height());
}

void LayoutObject::SetX(int x)
{
	SetBounds(x, y(), width(), height());
}

void LayoutObject::SetY(int y)
{
	SetBounds(x(), y, width(), height());
}

SPtr<LayoutObject> LayoutObject::GetParent() const
{
	return parent_.get();
}

void LayoutObject::SetParent(const SPtr<LayoutObject>& parent)
{
	parent_.reset(parent);
}
