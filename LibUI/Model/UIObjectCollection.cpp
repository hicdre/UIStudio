#include "stdafx.h"
#include "UIObjectCollection.h"

UIObjectCollection::UIObjectCollection(const SPtr<UIObject>& owner)
	: owner_(owner->GetWeak<UIObject>())
{

}

UIObjectCollection::~UIObjectCollection()
{

}

uint32 UIObjectCollection::GetIndexOf(const SPtr<UIObject>& obj)
{
	uint32 index = 0;
	for (auto object : objects_)
	{
		if (object == obj)
			return index;
		index++;
	}
	return -1;
}

void UIObjectCollection::Add(const SPtr<UIObject>& obj)
{
	obj->parent_.reset(owner_);
	objects_.push_back(obj);

	if (auto p = owner_.get())
		p->OnChildAdded(obj, objects_.size() -1);
}

void UIObjectCollection::Remove(const SPtr<UIObject>& obj)
{
	SPtr<UIObject> p = InternalRemove(obj);
	if (p)
	{
		if (SPtr<UIObject> owner = owner_.get())
		{
			owner->OnChildRemoved(p);
		}
		owner_.reset();
	}
}

SPtr<UIObject> UIObjectCollection::InternalRemove(const SPtr<UIObject>& obj)
{
	for (auto iter = objects_.begin(); iter != objects_.end(); iter++)
	{
		if (*iter == obj)
		{
			objects_.erase(iter);
			return obj;
		}
	}
	return nullptr;
}

SPtr<UIObject> UIObjectCollection::GetOwner()
{
	return owner_.get();
}


