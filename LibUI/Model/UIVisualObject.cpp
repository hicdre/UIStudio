#include "stdafx.h"
#include "UIVisualObject.h"

UIVisualObject::UIVisualObject()
{
	SetPathDirty(true);
}

UIVisualObject::~UIVisualObject()
{

}


base::Rect UIVisualObject::GetLocalBounds()
{
	base::Rect rc(GetBounds());
	return base::Rect(0, 0, rc.width(), rc.height());
}

void UIVisualObject::Render(const SPtr<RenderContext>& context)
{
	if (!IsVisible())
		return;

	
	//push transform
	SetClip(context);

	if (!IsContainer())
	{
		RenderFill(context);
		RenderStroke(context);
	}
	else
	{
		RenderChildren(context);
	}

	ResetClip(context);
	//pop transform
}

bool UIVisualObject::IsVisible()
{
	return !GetAttributes()->HasAttribute("visible")
		? true
		: GetAttributes()->GetAttributeBool("visible");
}

void UIVisualObject::SetVisible(bool v)
{
	GetAttributes()->SetAttributeBool("visible", v);
}

void UIVisualObject::RenderFill(const SPtr<RenderContext>& context)
{
	SPtr<AttributePaint> paint = GetFill();
	if (paint)
	{
		float opicaty = FixOpacityValue(GetFillOpacity() * GetOpacity());
		SPtr<RenderBrush> brush = paint->GetBrush(GetSelf<UIObject>(), context, opicaty);
		if (brush)
		{
			context->FillPath(brush, GetPath(context));
		}
	}
}

bool UIVisualObject::RenderStroke(const SPtr<RenderContext>& context)
{
	return true;
}

void UIVisualObject::SetClip(const SPtr<RenderContext>& context)
{
	//not impl
}

void UIVisualObject::ResetClip(const SPtr<RenderContext>& context)
{
	//not impl
}

bool UIVisualObject::IsContainer()
{
	return true;
}



