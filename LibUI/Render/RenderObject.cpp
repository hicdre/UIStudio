#include "stdafx.h"
#include "RenderObject.h"
#include "Property/UIObject.h"

RenderObject::RenderObject()
	: visible_(false)
{

}

RenderObject::~RenderObject()
{

}

void RenderObject::Render()
{
	//not implment
}

void RenderObject::Attatch(const SPtr<UIObject>& object)
{
	owner_.reset(object);
	object->EventVisibleChanged.AddW(GetWeak<RenderObject>(),
		&RenderObject::OnPropertyVisibleChangedInternal);
	OnPropertyVisibleChangedInternal(object);
}

void RenderObject::Detach()
{
	owner_.reset();
}

SPtr<UIObject> RenderObject::GetUIObject()
{
	return owner_.get();
}

void RenderObject::OnVisibleChanged()
{

}
 
void RenderObject::OnPropertyVisibleChangedInternal(const SPtr<UIObject>& obj)
{
	visible_ = obj->GetPropertyVisible();
	OnVisibleChanged();
}
