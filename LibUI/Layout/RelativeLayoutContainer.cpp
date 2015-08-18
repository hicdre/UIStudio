#include "stdafx.h"
#include "RelativeLayoutContainer.h"
#include "Model/UIObjectCollection.h"
#include "Model/UIObject.h"

RelativeLayoutContainer::RelativeLayoutContainer()
	: LayoutContainer(RelativeLayout)	
{

}

RelativeLayoutContainer::~RelativeLayoutContainer()
{

}

void RelativeLayoutContainer::Layout()
{
	if (!IsNeedsLayout())
		return;
	SPtr<UIObject> owner = children_->GetOwner();
	if (!owner)
		return;
	base::Rect bounds = owner->GetLayoutObject()->GetLocalBounds();
	for (auto child : *children_.get())
	{
		int x= 0;
		{
			SPtr<AttributeLength> v = child->GetWidth();
			if (v->IsPixel())
			{
				x = v->GetPixel();
			}
			else if (v->IsPercent())
			{
				x = v->GetPercent() * bounds.width();
			}
			else
			{
				x = 0;
			}
		}
		int y = 0;
		{
			SPtr<AttributeLength> v = child->GetHeight();
			if (v->IsPixel())
			{
				y = v->GetPixel();
			}
			else if (v->IsPercent())
			{
				y = v->GetPercent() * bounds.height();
			}
			else
			{
				y = 0;
			}
		}
		int w = 0;
		{
			SPtr<AttributeLength> v = child->GetWidth();
			if (v->IsPixel())
			{
				w = v->GetPixel();
			}
			else if (v->IsPercent())
			{
				w = v->GetPercent() * bounds.width();
			}
			else
			{
				w = child->GetLayoutObject()->GetPerferedSize().width();
			}
		}
		int h = 0;
		{
			SPtr<AttributeLength> v = child->GetHeight();
			if (v->IsPixel())
			{
				h = v->GetPixel();
			}
			else if (v->IsPercent())
			{
				h = v->GetPercent() * bounds.height();
			}
			else
			{
				h =  child->GetLayoutObject()->GetPerferedSize().width();
			}
		}

		child->GetLayoutObject()->SetBounds(x, y, w, h);
	}
}

