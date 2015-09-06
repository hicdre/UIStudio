#include "stdafx.h"
#include "UIBasicText.h"

UIBasicText::UIBasicText()
{

}

UIBasicText::~UIBasicText()
{

}

base::SizeF UIBasicText::GetTextLayoutSize()
{
	SPtr<UIVisualObject> obj = GetVisualParent();
	if (!obj)
		return base::SizeF();
	base::Rect bounds(obj->GetLocalBounds());

	return base::SizeF(bounds.width(), bounds.height());	
}
